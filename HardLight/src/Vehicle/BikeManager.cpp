#include "Vehicle/BikeManager.h"


int getRandInt(int low, int high)
{
	return rand() % high + low;
}

BikeManager::BikeManager(World* new_world, INIReader* new_config, PhysxAgent* init_pxAgent)
{
	srand ((unsigned int)time(NULL));
	config = new_config;
	world = new_world;
	pxAgent = init_pxAgent;


	// Initialize pairs of bike assignments
	BikeAssignment bikeAssign1;
	BikeAssignment bikeAssign2;
	BikeAssignment bikeAssign3;
	BikeAssignment bikeAssign4;
	BikeAssignment bikeAssign5;
	BikeAssignment bikeAssign6;
	BikeAssignment bikeAssign7;
	BikeAssignment bikeAssign8;

	bikeAssign1.bikeTexture = "../data/Textures/BikeTextureBlue.tga";
	bikeAssign1.bikeTransTexture = "../data/Textures/BikeTextureBlueTrans.tga";
	bikeAssign1.tailTexture = "../data/Textures/LightTrailRed.tga";

	bikeAssign2.bikeTexture = "../data/Textures/BikeTextureYellow.tga";
	bikeAssign2.bikeTransTexture = "../data/Textures/BikeTextureYellowTrans.tga";
	bikeAssign2.tailTexture = "../data/Textures/LightTrailYellow.tga";
	
	bikeAssign3.bikeTexture = "../data/Textures/BikeTextureLightBlue.tga";
	bikeAssign3.bikeTransTexture = "../data/Textures/BikeTextureLightBlueTrans.tga";
	bikeAssign3.tailTexture = "../data/Textures/LightTrailLightBlue.tga";

	bikeAssign4.bikeTexture = "../data/Textures/BikeTextureBlue.tga";
	bikeAssign4.bikeTransTexture = "../data/Textures/BikeTextureBlueTrans.tga";
	bikeAssign4.tailTexture = "../data/Textures/LightTrailBlue.tga";

	bikeAssign5.bikeTexture = "../data/Textures/BikeTextureLightGreen.tga";
	bikeAssign5.bikeTransTexture = "../data/Textures/BikeTextureLightGreenTrans.tga";
	bikeAssign5.tailTexture = "../data/Textures/LightTrailGreen.tga";

	bikeAssign6.bikeTexture = "../data/Textures/BikeTextureOrange.tga";
	bikeAssign6.bikeTransTexture = "../data/Textures/BikeTextureOrangeTrans.tga";
	bikeAssign6.tailTexture = "../data/Textures/LightTrailOrange.tga";
	
	bikeAssign7.bikeTexture = "../data/Textures/BikeTexturePink.tga";
	bikeAssign7.bikeTransTexture = "../data/Textures/BikeTexturePinkTrans.tga";
	bikeAssign7.tailTexture = "../data/Textures/LightTrailPink.tga";
	
	bikeAssign8.bikeTexture = "../data/Textures/BikeTexturePurple.tga";
	bikeAssign8.bikeTransTexture = "../data/Textures/BikeTexturePurpleTrans.tga";
	bikeAssign8.tailTexture = "../data/Textures/LightTrailPurple.tga";

	bikeAssignments.push_back(bikeAssign1);
	bikeAssignments.push_back(bikeAssign2);
	bikeAssignments.push_back(bikeAssign3);
	bikeAssignments.push_back(bikeAssign4);
	bikeAssignments.push_back(bikeAssign5);
	bikeAssignments.push_back(bikeAssign6);
	bikeAssignments.push_back(bikeAssign7);
	bikeAssignments.push_back(bikeAssign8);

	selectedIndex = getRandInt(0, bikeAssignments.size());	// Randomize starting texture assignment location for some variability

}

// Creates a player chassis, loads it onto the world and adds it to the player bike_manager vector
Bike* BikeManager::add_player_bike(Chassis* chassis, SDL_GameController* sdl_controller)
{
	Controller* controller = new Player_Controller(chassis, sdl_controller);
	Bike* new_bike = new Bike(chassis, PLAYER_BIKE, config, controller);
	world->add_entity(new_bike);

	// Assign proper textures
	selectedIndex = (selectedIndex + 1) % bikeAssignments.size();
	BikeAssignment bikeAssignment = bikeAssignments[selectedIndex];
	chassis->set_texture(TextureMap::Instance()->getTexture(bikeAssignment.bikeTexture));
	chassis->set_trans_texture(TextureMap::Instance()->getTexture(bikeAssignment.bikeTransTexture));
	new_bike->get_tail()->set_texture(TextureMap::Instance()->getTexture(bikeAssignment.tailTexture));
	player_bikes.push_back(new_bike);
	return new_bike;
}

// Creates a bot chassis, loads it onto the world and adds it to the bot bike_manager vector
Bike* BikeManager::add_bot_bike(Chassis* chassis)
{
	Controller* controller = new Bot_Controller(chassis);
	Bike* new_bike = new Bike(chassis, BOT_BIKE, config, controller);
	world->add_entity(new_bike);

	// Assign proper textures
	selectedIndex = (selectedIndex + 1) % bikeAssignments.size();
	BikeAssignment bikeAssignment = bikeAssignments[selectedIndex];
	chassis->set_texture(TextureMap::Instance()->getTexture(bikeAssignment.bikeTexture));
	chassis->set_trans_texture(TextureMap::Instance()->getTexture(bikeAssignment.bikeTransTexture));
	new_bike->get_tail()->set_texture(TextureMap::Instance()->getTexture(bikeAssignment.tailTexture));
	bot_bikes.push_back(new_bike);
	return new_bike;
}

vector<Bike*> BikeManager::get_all_bikes()
{
	vector<Bike*> all_bikes;
	all_bikes.reserve( player_bikes.size() + bot_bikes.size() ); // preallocate memory
	all_bikes.insert( all_bikes.end(), player_bikes.begin(), player_bikes.end() );
	all_bikes.insert( all_bikes.end(), bot_bikes.begin(), bot_bikes.end() );

	return all_bikes;
}

vector<Bike*> BikeManager::get_player_bikes()
{
	return player_bikes;
}

vector<Bike*> BikeManager::get_bot_bikes()
{
	return bot_bikes;
}

vector<Bike*> BikeManager::get_dead_bikes()
{
	return dead_bikes;
}
// Searches all bikes for the one with the corresponding chassis actor
Bike* BikeManager::get_bike(PxRigidActor* actor)
{
	for (unsigned int i = 0; i < player_bikes.size(); i++)
	{
		if (player_bikes[i]->get_chassis()->get_actor() == actor)
			return player_bikes[i];
	}

	for (unsigned int i = 0; i < bot_bikes.size(); i++)
	{
		if (bot_bikes[i]->get_chassis()->get_actor() == actor)
			return bot_bikes[i];
	}

	return NULL;
}

void BikeManager::kill_bike(Bike* bike)
{
	bike->set_renderable(false);		// Stop the bike from being rendered

	// Delete chassis px actor
	pxAgent->get_scene()->removeActor(*bike->get_chassis()->get_actor(), false);

	// Kill the tail of the bike
	bike->get_tail()->set_max_length(0);
	bike->get_tail()->update(pxAgent);

	// Remove the bike in question from its list
	if(bike->get_subtype() == PLAYER_BIKE)
	{
		for (unsigned int i = 0; i < player_bikes.size(); i++)
		{
			if (player_bikes[i]->get_chassis() == bike->get_chassis())
			{
				dead_bikes.push_back(player_bikes[i]);
				//player_bikes.erase(player_bikes.begin()+i);

				return;
			}
		}
	}

	else if(bike->get_subtype() == BOT_BIKE)
	{
		for (unsigned int i = 0; i < bot_bikes.size(); i++)
		{
			if (bot_bikes[i]->get_chassis() == bike->get_chassis())
			{
				dead_bikes.push_back(bot_bikes[i]);
				//bot_bikes.erase(bot_bikes.begin()+i);
				return;
			}
		}
	}
	cerr << "ERROR: Could not delete bike from world!" << endl;	// If the bike couldnt be deleted, we will fall onto this error message.
}

void BikeManager::clear_controllers() {
	for(Bike* bike : get_all_bikes()) 
	{
		if(bike->get_subtype() == PLAYER_BIKE)
			delete (Player_Controller*)bike->get_controller();
		else if(bike->get_subtype() == BOT_BIKE)
			delete (Bot_Controller*)bike->get_controller();
	}
}
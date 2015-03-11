#include "Vehicle/BikeManager.h"


BikeManager::BikeManager(World* new_world, INIReader* new_config, PhysxAgent* init_pxAgent)
{
	srand ((unsigned int)time(NULL));
	config = new_config;
	world = new_world;
	pxAgent = init_pxAgent;
}

int getRandInt(int low, int high)
{
	return rand() % high + low;
}

// Creates a player chassis, loads it onto the world and adds it to the player bike_manager vector
void BikeManager::add_player_bike(Chassis* chassis, SDL_GameController* sdl_controller)
{
	Controller* controller = new Player_Controller(chassis, sdl_controller);
	Bike* new_bike = new Bike(chassis, PLAYER_BIKE, config, controller);
	world->add_entity(new_bike);
	int someInt = getRandInt(1,4);
	string randTexturestr =  "../data/Textures/BikeTexture" + to_string(someInt) + ".tga";
	char const * randTexture =  randTexturestr.c_str();
	chassis->set_texture(TextureMap::Instance()->getTexture(randTexture));
	player_bikes.push_back(new_bike);
}

//// Creates a player chassis, loads it onto the world and adds it to the player bike_manager vector
//void BikeManager::add_player_bike(Chassis* chassis, KeyMapping keymapping)
//{
//	//Bike* new_bike = new Bike(chassis, PLAYER_BIKE);
//	//world->add_entity(new_bike);
//	//new_bike->set_subtype(PLAYER_BIKE);
//
//	world->add_entity(chassis);
//	int someInt = getRandInt(1,4);
//	string randTexturestr =  "../data/Textures/BikeTexture" + to_string(someInt) + ".tga";
//	char const * randTexture =  randTexturestr.c_str();
//	chassis->set_texture(TextureMap::Instance()->getTexture(randTexture));
//	chassis->set_subtype(PLAYER_BIKE);
//	Controller * controlled = new Player_Controller(chassis, keymapping);
//	//controlled_bikes.push_back(controlled);
//	player_bikes.push_back(chassis);
//	add_tail(chassis);
//}

// Creates a bot chassis, loads it onto the world and adds it to the bot bike_manager vector
void BikeManager::add_bot_bike(Chassis* chassis)
{
	Controller* controller = new Bot_Controller(chassis);
	Bike* new_bike = new Bike(chassis, BOT_BIKE, config, controller);
	world->add_entity(new_bike);
	int someInt = getRandInt(1,4);
	string randTexturestr =  "../data/Textures/BikeTexture" + to_string(someInt) + ".tga";
	char const * randTexture =  randTexturestr.c_str();
	chassis->set_texture(TextureMap::Instance()->getTexture(randTexture));
	player_bikes.push_back(new_bike);
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

	// Kill the tail of the bike
	bike->get_tail()->set_max_length(0);
	bike->get_tail()->update(pxAgent);
	
	for (unsigned int i = 0; i < player_bikes.size(); i++)
	{
		if (player_bikes[i]->get_chassis() == bike->get_chassis())
		{
			dead_bikes.push_back(player_bikes[i]);
			player_bikes.erase(player_bikes.begin()+i);
			return;
		}
	}

	for (unsigned int i = 0; i < bot_bikes.size(); i++)
	{
		if (bot_bikes[i]->get_chassis() == bike->get_chassis())
		{
			dead_bikes.push_back(bot_bikes[i]);
			bot_bikes.erase(bot_bikes.begin()+i);
			return;
		}
	}
}

void BikeManager::clear_controllers() {
	for(Bike* bike : get_all_bikes()) 
	{
		delete bike->get_controller();;
	}
}
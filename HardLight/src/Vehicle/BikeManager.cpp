#include "Vehicle/BikeManager.h"


BikeManager::BikeManager(World* new_world, INIReader* new_config)
{
	srand ((unsigned int)time(NULL));
	config = new_config;
	world = new_world;
}

int getRandInt(int low, int high)
{
	return rand() % high + low;
}

// Creates a player chassis, loads it onto the world and adds it to the player bike_manager vector
void BikeManager::add_player_bike(Chassis* chassis, SDL_GameController* sdl_controller)
{
	//Bike* new_bike = new Bike(chassis, PLAYER_BIKE);
	//world->add_entity(new_bike);
	//new_bike->set_subtype(PLAYER_BIKE);

	world->add_entity(chassis);
	int someInt = getRandInt(1,4);
	string randTexturestr =  "../data/Textures/BikeTexture" + to_string(someInt) + ".tga";
	char const * randTexture =  randTexturestr.c_str();
	chassis->set_texture(TextureMap::Instance()->getTexture(randTexture));
	chassis->set_subtype(PLAYER_BIKE);
	Controller * controlled = new Player_Controller(chassis, sdl_controller);
	controlled_bikes.push_back(controlled);
	player_bikes.push_back(chassis);
	add_tail(chassis);
}

// Adds a tail wall to the world and the tail walls vector
void BikeManager::add_tail(Chassis* chassis)
{
	TailWall* tail_wall = new TailWall(chassis, config);
	tail_walls.push_back(tail_wall);
	world->add_entity(tail_wall);
}

// Creates a bot chassis, loads it onto the world and adds it to the bot bike_manager vector
void BikeManager::add_bot_bike(Chassis* chassis)
{
	world->add_entity(chassis);
	int someInt = getRandInt(1,4);
	string randTexturestr =  "../data/Textures/BikeTexture" + to_string(someInt) + ".tga";
	char const * randTexture =  randTexturestr.c_str();
	chassis->set_texture(TextureMap::Instance()->getTexture(randTexture));
	chassis->set_subtype(BOT_BIKE);
	Controller * controlled = new Bot_Controller(chassis);
	controlled_bikes.push_back(controlled);
	bot_bikes.push_back(chassis);
	add_tail(chassis);
}

vector<Chassis*> BikeManager::get_all_bikes()
{
	vector<Chassis*> all_bikes;
	all_bikes.reserve( player_bikes.size() + bot_bikes.size() ); // preallocate memory
	all_bikes.insert( all_bikes.end(), player_bikes.begin(), player_bikes.end() );
	all_bikes.insert( all_bikes.end(), bot_bikes.begin(), bot_bikes.end() );

	return all_bikes;
}

vector<Chassis*> BikeManager::get_player_bikes()
{
	return player_bikes;
}

vector<Chassis*> BikeManager::get_bot_bikes()
{
	return bot_bikes;
}

vector<Controller*> BikeManager::get_controlled_bikes()
{
	return controlled_bikes;
}

Chassis* BikeManager::get_bike(PxRigidActor* actor)
{
	for (unsigned int i = 0; i < player_bikes.size(); i++)
	{
		if (player_bikes[i]->get_actor() == actor)
			return player_bikes[i];
	}

	for (unsigned int i = 0; i < bot_bikes.size(); i++)
	{
		if (bot_bikes[i]->get_actor() == actor)
			return bot_bikes[i];
	}

	return NULL;
}

void BikeManager::kill_bike(Chassis* chassis)
{
	chassis->set_renderable(false);
	for (unsigned int i = 0; i < tail_walls.size(); i++)
	{
		if (tail_walls[i]->getBike() == chassis)
		{
			tail_walls[i]->set_max_length(0);
		}
	}

	for (unsigned int i = 0; i < player_bikes.size(); i++)
	{
		if (player_bikes[i] == chassis)
		{
			dead_bikes.push_back(player_bikes[i]);
			player_bikes.erase(player_bikes.begin()+i);
			return;
		}
	}

	for (unsigned int i = 0; i < bot_bikes.size(); i++)
	{
		if (bot_bikes[i] == chassis)
		{
			dead_bikes.push_back(bot_bikes[i]);
			bot_bikes.erase(bot_bikes.begin()+i);
			return;
		}
	}
}

vector<TailWall*> BikeManager::get_all_tails()
{
	return tail_walls;
}

void BikeManager::clear_controllers() {
	for(Controller* controller : controlled_bikes) {
		delete controller;
	}
	controlled_bikes.clear();
}

void BikeManager::extend_tail(Chassis* chassis)
{
	for (unsigned int i = 0; i < tail_walls.size(); i++)
	{
		if (tail_walls[i]->getBike() == chassis)
		{
			tail_walls[i]->extend_max_length();
			return;
		}
	}
}
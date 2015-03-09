#include "Vehicle/Bikes.h"


Bikes::Bikes(World* new_world, INIReader* new_config)
{
	srand ((unsigned int)time(NULL));
	config = new_config;
	world = new_world;
}

int getRandInt(int low, int high)
{
	return rand() % high + low;
}

// Creates a player bike, loads it onto the world and adds it to the player bikes vector
void Bikes::add_player_bike(Bike* bike, SDL_GameController* sdl_controller)
{
	world->add_entity(bike);
	int someInt = getRandInt(1,4);
	string randTexturestr =  "../data/Textures/BikeTexture" + to_string(someInt) + ".tga";
	char const * randTexture =  randTexturestr.c_str();
	bike->set_texture(TextureMap::Instance()->getTexture(randTexture));
	player_bikes.push_back(bike);
	add_tail(bike);
}

// Adds a tail wall to the world and the tail walls vector
void Bikes::add_tail(Bike* bike)
{
	TailWall* tail_wall = new TailWall(bike, config);
	tail_walls.push_back(tail_wall);
	world->add_entity(tail_wall);
}

// Creates a bot bike, loads it onto the world and adds it to the bot bikes vector
void Bikes::add_bot_bike(Bike* bike)
{
	world->add_entity(bike);
	int someInt = getRandInt(1,4);
	string randTexturestr =  "../data/Textures/BikeTexture" + to_string(someInt) + ".tga";
	char const * randTexture =  randTexturestr.c_str();
	bike->set_texture(TextureMap::Instance()->getTexture(randTexture));
	Controller * controlled = new Bot_Controller(bike);
	controlled_bikes.push_back(controlled);
	bot_bikes.push_back(bike);
	add_tail(bike);
}

vector<Bike*> Bikes::get_all_bikes()
{
	vector<Bike*> all_bikes;
	all_bikes.reserve( player_bikes.size() + bot_bikes.size() ); // preallocate memory
	all_bikes.insert( all_bikes.end(), player_bikes.begin(), player_bikes.end() );
	all_bikes.insert( all_bikes.end(), bot_bikes.begin(), bot_bikes.end() );

	return all_bikes;
}

vector<Bike*> Bikes::get_player_bikes()
{
	return player_bikes;
}

vector<Bike*> Bikes::get_bot_bikes()
{
	return bot_bikes;
}

vector<Controller*> Bikes::get_controlled_bikes()
{
	return controlled_bikes;
}

Bike* Bikes::get_bike(PxRigidActor* actor)
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

void Bikes::kill_bike(Bike* bike)
{
	bike->set_deleted(true);
	
	for (unsigned int i = 0; i < tail_walls.size(); i++)
	{
		if (tail_walls[i]->getBike() == bike)
		{
			tail_walls[i]->set_max_length(0);
		}
	}

	for (unsigned int i = 0; i < player_bikes.size(); i++)
	{
		if (player_bikes[i] == bike)
		{
			dead_bikes.push_back(player_bikes[i]);
			player_bikes.erase(player_bikes.begin()+i);
			return;
		}
	}

	for (unsigned int i = 0; i < bot_bikes.size(); i++)
	{
		if (bot_bikes[i] == bike)
		{
			dead_bikes.push_back(bot_bikes[i]);
			bot_bikes.erase(bot_bikes.begin()+i);
			return;
		}
	}

}

vector<TailWall*> Bikes::get_all_tails()
{
	return tail_walls;
}
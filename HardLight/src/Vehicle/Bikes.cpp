#include "Vehicle/Bikes.h"
#include "Controls/Player_Controller.h"
#include "Controls/Bot_Controller.h"

void Bikes::add_player_bike(Bike* bike, SDL_GameController* sdl_controller)
{
	//bike->set_controller(new Player_Controller(sdl_controller));
	player_bikes.push_back(bike);
}

void Bikes::add_bot_bike(Bike* bike)
{
	Controller * controlled = new Bot_Controller(bike);
	controlled_bikes.push_back(controlled);
	bot_bikes.push_back(bike);
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
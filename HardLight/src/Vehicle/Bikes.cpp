#include "Vehicle/Bikes.h"
#include "Vehicle/Player_Bike.h"

void Bikes::add_player_bike(Bike* bike, SDL_GameController* controller)
{
	((Player_Bike*)bike)->set_controller(controller);
	player_bikes.push_back(((Player_Bike*)bike));
}

void Bikes::add_bot_bike(Bike* bike)
{
	//bike->set_controller(controller);
	bot_bikes.push_back(((Bot_Bike*)bike));
}

vector<Bike*> Bikes::get_all_bikes()
{
	vector<Bike*> all_bikes;
	all_bikes.reserve( player_bikes.size() + bot_bikes.size() ); // preallocate memory
	all_bikes.insert( all_bikes.end(), player_bikes.begin(), player_bikes.end() );
	all_bikes.insert( all_bikes.end(), bot_bikes.begin(), bot_bikes.end() );

	return all_bikes;
}

vector<Player_Bike*> Bikes::get_player_bikes()
{
	return player_bikes;
}

vector<Bot_Bike*> Bikes::get_bot_bikes()
{
	return bot_bikes;
}
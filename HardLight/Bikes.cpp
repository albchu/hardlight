#include "Bikes.h"

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
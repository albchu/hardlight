#include "Bikes.h"

vector<Bike*> Bikes::get_all_bikes()
{
	vector<Bike*> all_bikes;
	all_bikes.reserve( user_bikes.size() + bot_bikes.size() ); // preallocate memory
	all_bikes.insert( all_bikes.end(), user_bikes.begin(), user_bikes.end() );
	all_bikes.insert( all_bikes.end(), bot_bikes.begin(), bot_bikes.end() );

	return all_bikes;
}

vector<Bike*> Bikes::get_user_bikes()
{
	return user_bikes;
}

vector<Bike*> Bikes::get_bot_bikes()
{
	return bot_bikes;
}
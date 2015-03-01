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
	//bike->set_controller(new Bot_Controller());
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
 
// This class holds pointers to all bikes
#ifndef _BIKES_H
#define _BIKES_H

#include "Bike.h"
#include "Player_Bike.h"
#include "Bot_Bike.h"
#include <vector>
#include <SDL.h>

using namespace std;

class Bikes
{
public:
	void add_bot_bike(Bike* bike);
	void add_player_bike(Player_Bike* bike, SDL_GameController* controller);
	vector<Bike*> get_all_bikes();
	vector<Player_Bike*> get_player_bikes();
	vector<Bike*> get_bot_bikes();

private:
	vector<Player_Bike*> player_bikes;
	vector<Bike*> bot_bikes;
};

#endif
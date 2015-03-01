// This class holds pointers to all bikes
#ifndef _BIKES_H
#define _BIKES_H

#include "Bike.h"
#include <vector>
#include <SDL.h>

using namespace std;

class Bikes
{
public:
	void add_bot_bike(Bike* bike);
	void add_player_bike(Bike* bike, SDL_GameController* controller);
	vector<Bike*> get_all_bikes();
	vector<Player_Bike*> get_player_bikes();
	vector<Bot_Bike*> get_bot_bikes();
	Bike* get_bike(PxRigidActor* actor);
	void kill_bike(Bike* bike);

private:
	vector<Player_Bike*> player_bikes;
	vector<Bot_Bike*> bot_bikes;
	vector<Bike*> dead_bikes;
	vector<Bike*> get_player_bikes();
	vector<Bike*> get_bot_bikes();

private:
	vector<Bike*> player_bikes;
	vector<Bike*> bot_bikes;
};

#endif
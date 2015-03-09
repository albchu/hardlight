// This class holds pointers to all bikes
#ifndef _BIKES_H
#define _BIKES_H

#include "World.h"
#include "TailWall.h"
//#include "Bike.h"
#include "Controls/Controller.h"
#include "Controls/Player_Controller.h"
#include "Controls/Bot_Controller.h"
#include "Common.h"
#include "Rendering/TextureMap.h"

#include <vector>
#include <SDL.h>


using namespace std;

class Bikes
{
public:
	Bikes(World* new_world, INIReader* new_config);
	void add_bot_bike(Bike* bike);
	void add_player_bike(Bike* bike, SDL_GameController* controller);
	vector<Bike*> get_all_bikes();
	vector<Bike*> get_player_bikes();
	vector<TailWall*> get_all_tails();
	vector<Bike*> get_bot_bikes();
	vector<Controller*> get_controlled_bikes();
	Bike* get_bike(PxRigidActor* actor);
	void kill_bike(Bike* bike);
	void add_tail(Bike* bike);
	void clear_controllers();
	void extend_tail(Bike* bike);

private:
	vector<Bike*> player_bikes;
	vector<Bike*> bot_bikes;
	vector<Bike*> dead_bikes;
	vector<Controller*> controlled_bikes;
	vector<TailWall*> tail_walls;
	World* world;
	INIReader* config;
};

#endif
// This class holds pointers to all bike_manager
#ifndef _BIKES_H
#define _BIKES_H

#include "World.h"
#include "TailWall.h"
//#include "Chassis.h"
#include "Controls/Controller.h"
#include "Controls/Player_Controller.h"
#include "Controls/Bot_Controller.h"
#include "Common.h"
#include "Rendering/TextureMap.h"

#include <vector>
#include <SDL.h>


using namespace std;

class BikeManager
{
public:
	BikeManager(World* new_world, INIReader* new_config);
	void add_bot_bike(Chassis* bike);
	void add_player_bike(Chassis* bike, SDL_GameController* controller);
	vector<Chassis*> get_all_bikes();
	vector<Chassis*> get_player_bikes();
	vector<TailWall*> get_all_tails();
	vector<Chassis*> get_bot_bikes();
	vector<Controller*> get_controlled_bikes();
	Chassis* get_bike(PxRigidActor* actor);
	void kill_bike(Chassis* bike);
	void add_tail(Chassis* bike);
	void clear_controllers();
	void extend_tail(Chassis* bike);

private:
	vector<Chassis*> player_bikes;
	vector<Chassis*> bot_bikes;
	vector<Chassis*> dead_bikes;
	vector<Controller*> controlled_bikes;
	vector<TailWall*> tail_walls;
	World* world;
	INIReader* config;
};

#endif
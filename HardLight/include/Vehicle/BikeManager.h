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
#include "Vehicle/Bike.h"

#include <vector>
#include <SDL.h>


using namespace std;

class BikeManager
{
public:
	BikeManager(World* new_world, INIReader* new_config);
	void add_bot_bike(Chassis* bike);
	void add_player_bike(Chassis* bike, SDL_GameController* controller);
	void add_player_bike(Chassis* chassis, KeyMapping keymapping);
	vector<Bike*> get_all_bikes();
	vector<Bike*> get_player_bikes();
	vector<Bike*> get_bot_bikes();
	Bike* get_bike(PxRigidActor* actor);
	void kill_bike(Bike* bike);
	void clear_controllers();

private:
	vector<Bike*> player_bikes;
	vector<Bike*> bot_bikes;
	vector<Bike*> dead_bikes;
	World* world;
	INIReader* config;
};

#endif
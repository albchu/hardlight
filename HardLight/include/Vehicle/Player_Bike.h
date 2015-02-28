#ifndef _PLAYER_BIKE_H
#define _PLAYER_BIKE_H

#include "Vehicle/Bike.h"
#include <SDL.h>

using namespace glm;
using namespace std;

class Player_Bike : public Bike
{

public:
	SDL_GameController* getController();
	void set_controller(SDL_GameController*);
private:
	SDL_GameController* controller;
};
#endif
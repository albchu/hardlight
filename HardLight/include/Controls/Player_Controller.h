#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

#include "Controls/Controller.h"
#include <SDL.h>

class Player_Controller : public Controller
{
public:
	Player_Controller(Bike* bike, SDL_GameController* controller);
	//void forward();

private:
	SDL_GameController* sdl_controller;
};
#endif
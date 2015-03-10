#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

#include "Controls/Controller.h"
#include <SDL.h>

class Player_Controller : public Controller
{
public:
	Player_Controller(Chassis* bike, SDL_GameController* controller);
	void update();
	//void forward();

private:
	SDL_GameController* sdl_controller;
	int deadZone;
};
#endif
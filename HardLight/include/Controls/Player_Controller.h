#ifndef _PLAYER_CONTROLLER_H
#define _PLAYER_CONTROLLER_H

#include "Controls/Controller.h"
#include "KeyMappings.h"
#include <SDL.h>

class Player_Controller : public Controller
{
public:
	// One of these two should be used to instantiate a player controller
	Player_Controller(Chassis* bike, SDL_GameController* controller);
	Player_Controller(Chassis* new_bike, KeyMapping init_keys);

	SDL_GameController* get_controller();
	int get_dead_zone();
	KeyMapping get_key_controls();
	void init_values();

private:
	SDL_GameController* sdl_controller;
	int deadZone;
	KeyMapping key_controls;
};
#endif
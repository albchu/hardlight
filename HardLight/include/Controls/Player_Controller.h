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
	~Player_Controller();
	SDL_GameController* get_controller();
	int get_dead_zone();
	KeyMapping get_key_controls();
	float get_camera_right();
	void set_camera_right(float);
	float get_camera_up();
	void set_camera_up(float);
	void init_values();
	void init_rumble();
	void rumble(float strength, int duration);

private:
	SDL_GameController* sdl_controller;
	SDL_Haptic* gControllerHaptic;
	int camera_deadZone;
	KeyMapping key_controls;
	float camera_right;
	float camera_up;
};
#endif
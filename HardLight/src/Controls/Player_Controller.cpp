#include "Controls/Player_Controller.h"

Player_Controller::Player_Controller(Chassis* new_chassis, SDL_GameController* new_sdl_controller)
{
	init_values();
	chassis = new_chassis;
	sdl_controller = new_sdl_controller;
}

Player_Controller::Player_Controller(Chassis* new_chassis, KeyMapping init_keys)
{
	init_values();
	chassis = new_chassis;
	key_controls = init_keys;
}

void Player_Controller::init_values()
{
	cout << "Player controller has been set!" << endl;

	sdl_controller = NULL;
	max_acceleration = 1.0;
	min_acceleration = 0.5;
	acceleration = min_acceleration;
	direction = 0.0;
	deadZone = 8000;
	steeringMethod = NULL;
	motionMethod = NULL;
}

SDL_GameController* Player_Controller::get_controller()
{
	return sdl_controller;
}

int Player_Controller::get_dead_zone()
{
	return deadZone;
}

KeyMapping Player_Controller::get_key_controls()
{
	return key_controls;
}


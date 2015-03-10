#include "Controls/Player_Controller.h"

Player_Controller::Player_Controller(Chassis* new_bike, SDL_GameController* new_sdl_controller)
{
	cout << "Player controller has been set!" << endl;
	bike = new_bike;
	sdl_controller = new_sdl_controller;
	max_acceleration = 1.0;
	min_acceleration = 0.5;
	deadZone = 8000;
}

// Get all controller input and set the proper callbacks
void Player_Controller::update()
{
	int LeftX = SDL_GameControllerGetAxis(sdl_controller, SDL_CONTROLLER_AXIS_LEFTX);
	int RightX = SDL_GameControllerGetAxis(sdl_controller, SDL_CONTROLLER_AXIS_RIGHTX);
	int RightY = SDL_GameControllerGetAxis(sdl_controller, SDL_CONTROLLER_AXIS_RIGHTY);
	float accel = get_min_acceleration(); // Default acceleration to minimum if non is given
	PxReal steer = 0.0;

	if (LeftX < -deadZone || LeftX > deadZone)
	{
		steer = (LeftX)/(-32768.0f); //the axis are inverted on the controller
	}

	if(SDL_GameControllerGetAxis(sdl_controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0)
	{
		accel = SDL_GameControllerGetAxis(sdl_controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)/32768.0f;
		// Cap the speed into a specific range
		if (accel < get_min_acceleration())
			accel = get_min_acceleration();
		if (accel > get_max_acceleration())
			accel = get_max_acceleration();
	}
	this->set_motion(&Controller::forward);
	this->set_steering(&Controller::steer);
	this->set_direction(steer);
	this->set_acceleration(accel);

}


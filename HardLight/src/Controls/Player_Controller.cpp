#include "Controls/Player_Controller.h"

Player_Controller::Player_Controller(Bike* new_bike, SDL_GameController* new_sdl_controller)
{
	cout << "Player controller has been set!" << endl;
	bike = new_bike;
	sdl_controller = new_sdl_controller;
}


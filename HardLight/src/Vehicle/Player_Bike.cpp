#include "Vehicle/Player_Bike.h"

SDL_GameController* Player_Bike::getController()
{
	return controller; 
}


void Player_Bike::set_controller(SDL_GameController* new_controller)
{
	controller = new_controller;
}


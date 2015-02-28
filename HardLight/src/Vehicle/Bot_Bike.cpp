#include "Vehicle/Bot_Bike.h"

Bot_Controller* Bot_Bike::getController()
{
	return controller; 
}


void Bot_Bike::set_controller(Bot_Controller* new_controller)
{
	controller = new_controller;
}


#include "Vehicle/Bike.h"

Bike::Bike(Chassis* init_chassis, BikeSubTypes init_subtype, INIReader* new_config, Controller* new_controller)
{
	config = new_config;
	chassis = init_chassis;
	type = BIKE;
	subtype = init_subtype;

	// Initialize tail
	tailwall = new TailWall(chassis, config);

	// Initialize controller 
	controller = new_controller;

}

Bike::~Bike()
{

}

Chassis* Bike::get_chassis()
{
	return chassis;
}

TailWall* Bike::get_tail()
{
	return tailwall;
}


BikeSubTypes Bike::get_subtype()
{
	return subtype;
}

Controller* Bike::get_controller()
{
	return controller;
}


void Bike::set_subtype(BikeSubTypes new_subtype)
{
	subtype = new_subtype;
}

void Bike::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	chassis->render(projection_matrix,view_matrix,lightPos);
	tailwall->render(projection_matrix,view_matrix,lightPos);
}

void Bike::set_hold_powerup(Powerup<Hold>::PowerCallback new_powerup)
{
	powerup = new_powerup;
}

void Bike::execute_hold_powerup()
{
	Hold hold;
	(hold.*powerup)(chassis, tailwall, config);
}


void Bike::execute_instant_powerup(Powerup<Instant>::PowerCallback powerup)
{
	Instant instant;
	(instant.*powerup)(chassis, tailwall, config);
}

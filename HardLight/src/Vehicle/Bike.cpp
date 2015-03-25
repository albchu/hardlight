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
	powerup = NULL;
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
	if(powerup != NULL)	// Only execute callback if its been set
	{
		(hold.*powerup)(chassis, tailwall, config);
		powerup = NULL;	// Clear the powerup once its used
	}
}


void Bike::execute_instant_powerup(Powerup<Instant>::PowerCallback instant_powerup)
{
	Instant instant;
	(instant.*instant_powerup)(chassis, tailwall, config);
}

Powerup<Hold>::PowerCallback Bike::get_hold_powerup()
{
	return powerup;
}

PxVec3 Bike::get_gravity_up()
{
	return get_chassis()->get_gravity_up();
}

void Bike::set_gravity_up(PxVec3 new_gravity)
{
	get_chassis()->set_gravity_up(new_gravity);
}


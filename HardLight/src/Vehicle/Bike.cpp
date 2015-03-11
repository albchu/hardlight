#include "Vehicle/Bike.h"

Bike::Bike(Chassis* init_chassis, BikeSubTypes init_subtype)
{
	chassis = init_chassis;
	type = BIKE;
	subtype = init_subtype;

	// Initialize controller 
}

Bike::~Bike()
{

}

Chassis* Bike::get_chassis()
{
	return chassis;
}


BikeSubTypes Bike::get_subtype()
{
	return subtype;
}

void Bike::set_subtype(BikeSubTypes new_subtype)
{
	subtype = new_subtype;
}

void Bike::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	chassis->render(projection_matrix,view_matrix,lightPos);
}
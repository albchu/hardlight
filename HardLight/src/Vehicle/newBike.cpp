#include "Vehicle/newBike.h"

newBike::newBike(Bike* new_chassis)
{
	chassis = new_chassis;
}

newBike::~newBike()
{

}


BikeSubTypes newBike::get_subtype()
{
	return subtype;
}

void newBike::set_subtype(BikeSubTypes new_subtype)
{
	subtype = new_subtype;
}

void newBike::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
}
#include "Pickup.h"

Pickup::Pickup()
{
	type = PICKUP;
	draw_mode = GL_TRIANGLES;
	mesh_data = MeshMap::Instance()->getEntityMesh("HardLightPickup.obj");
	deleted = false;
}

Pickup::~Pickup(){}
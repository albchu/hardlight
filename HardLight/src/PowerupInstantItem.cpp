#include "PowerupInstantItem.h"

PowerupInstantItem::PowerupInstantItem(Powerup<Instant>::PowerCallback new_power, PxRigidActor* init_actor)
{
	powerup = new_power;
	type = WALL;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("powerup_random.obj");
	texture = TextureMap::Instance()->getTexture("UVTexture.tga");
	init_opengl();
	renderable = true;
}

PowerupInstantItem::~PowerupInstantItem()
{
	powerup = NULL;
}

Powerup<Instant>::PowerCallback PowerupInstantItem::get_powerup()
{
	return powerup;
}
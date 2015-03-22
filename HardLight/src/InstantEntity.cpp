#include "InstantEntity.h"

InstantEntity::InstantEntity(Powerup<Instant>::PowerCallback new_power, PxRigidActor* init_actor)
{
	powerup = new_power;
	type = WALL;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("powerup_random.obj");
	texture = TextureMap::Instance()->getTexture("../data/Textures/UVTexture.tga");
	init_opengl();
	renderable = true;
}

InstantEntity::~InstantEntity()
{
	powerup = NULL;
}

Powerup<Instant>::PowerCallback InstantEntity::get_powerup()
{
	return powerup;
}

void InstantEntity::set_powerup(Powerup<Instant>::PowerCallback new_power)
{
	powerup = new_power;
}



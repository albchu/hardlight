#include "HoldEntity.h"

HoldEntity::HoldEntity(Powerup<Hold>::PowerCallback new_power, PxRigidActor* init_actor)
{
	powerup = new_power;
	type = WALL;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("HardLightBike2.obj");
	texture = TextureMap::Instance()->getTexture("../data/Textures/UVTexture.tga");
	init_opengl();
	renderable = true;
}

HoldEntity::~HoldEntity()
{
	powerup = NULL;
}

Powerup<Hold>::PowerCallback HoldEntity::get_powerup()
{
	return powerup;
}
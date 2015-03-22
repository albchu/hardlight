#include "HoldEntity.h"

HoldEntity::HoldEntity(Powerup<Hold>::PowerCallback new_power, PxRigidActor* init_actor)
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

HoldEntity::~HoldEntity()
{
	cout << "Hold entity deconstructor" <<endl;
	powerup = NULL;
	mesh_data = NULL;
	texture = NULL;
	renderable = false;
	actor->release();
	
}

Powerup<Hold>::PowerCallback HoldEntity::get_powerup()
{
	return powerup;
}

void HoldEntity::set_powerup(Powerup<Hold>::PowerCallback new_power)
{
	powerup = new_power;
}
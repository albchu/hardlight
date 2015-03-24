#include "Powerup/InstantEntity.h"

InstantEntity::InstantEntity(Powerup<Instant>::PowerCallback new_power, PxRigidActor* init_actor, vec3 new_scaleFactors)
{
	powerup = new_power;
	type = WALL;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("PowerUp.obj");
	texture = TextureMap::Instance()->getTexture("../data/Textures/PowerUpBlue.tga");
	init_opengl();
	renderable = true;
	scaleFactors = new_scaleFactors;
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


mat4 InstantEntity::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);

	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
	model_matrix = scale(model_matrix, scaleFactors);

	return model_matrix;
}

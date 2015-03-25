#include "Powerup/HoldEntity.h"

HoldEntity::HoldEntity(Powerup<Hold>::PowerCallback new_power, PxRigidActor* init_actor, vec3 new_scaleFactors)
{
	powerup = new_power;
	type = WALL;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("powerup_random.obj");
	texture = TextureMap::Instance()->getTexture("../data/Textures/PowerUpRed.tga");
	init_opengl();
	renderable = true;
	scaleFactors = new_scaleFactors;
}

Powerup<Hold>::PowerCallback HoldEntity::get_powerup()
{
	return powerup;
}

void HoldEntity::set_powerup(Powerup<Hold>::PowerCallback new_power)
{
	powerup = new_power;
}

mat4 HoldEntity::get_model_matrix()
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
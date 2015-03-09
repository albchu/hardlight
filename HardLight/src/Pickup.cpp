#include "Pickup.h"

float Pickup::random_float(float low, float high)
{
	float random = (float)rand()/(float)RAND_MAX;
	return (((high-low)*random)+low);
}

Pickup::Pickup(INIReader* config, PhysxAgent* pxAgent, float init_arena_size)
{
	border = 20.0f;
	srand((unsigned int)time(NULL));
	arena_size = init_arena_size;
	type = PICKUP;
	draw_mode = GL_TRIANGLES;
	mesh_data = MeshMap::Instance()->getEntityMesh("tail.obj");
	texture = TextureMap::Instance()->getTexture("../data/Textures/LightTrail3.tga");
	init_opengl();
	deleted = false;

	scaleFactors = vec3(10.0f, 10.0f, 10.0f);

	maxPickups = config->GetInteger("pickup", "maxPickups", 1);
	heightOffFloor = (float)config->GetReal("pickup", "heightOffFloor", 0.0f);

	vec3 normal(0.0f, 1.0f, 0.0f);

	float x = random_float(-arena_size+border, arena_size-border);
	float z = random_float(-arena_size+border, arena_size-border);

	// Create physx actor and model centered at 'point'
	actor = pxAgent->create_pickup(vec3(x, heightOffFloor, z), normal, scaleFactors);
}

mat4 Pickup::get_model_matrix()
{
	PxTransform gPose = actor->getGlobalPose();
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);

	mat4 t_matrix = translate(vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	mat4 r_matrix = rotate(rads, vec3(axis.x, axis.y, axis.z));
	mat4 s_matrix = glm::scale(scaleFactors);

	return t_matrix * r_matrix * s_matrix;
}

void Pickup::respawn()
{
	float x = random_float(-arena_size+border, arena_size-border);
	float z = random_float(-arena_size+border, arena_size-border);

	// Create physx actor and model centered at 'point'
	actor->setGlobalPose(PxTransform(PxVec3(x, heightOffFloor, z), actor->getGlobalPose().q));
}
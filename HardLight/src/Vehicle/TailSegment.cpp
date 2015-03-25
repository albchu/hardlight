#include "Vehicle/TailSegment.h"

TailSegment::TailSegment(PxRigidActor* init_actor, const char * texturePath, float init_width, float init_height, float init_length, GLuint init_program_id)
{
	width = init_width;
	height = init_height;
	length = init_length+0.1f;
	type = WALL;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("tail.obj");
	texture = TextureMap::Instance()->getTexture(texturePath);
	init_opengl(init_program_id);
	renderable = true;
}

mat4 TailSegment::get_model_matrix()
{
	PxTransform gPose = actor->getGlobalPose();
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);

	mat4 t_matrix = translate(vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	mat4 r_matrix = rotate(rads, vec3(axis.x, axis.y, axis.z));
	mat4 s_matrix = scale(vec3(width, height, length));

	return t_matrix * r_matrix * s_matrix;
}

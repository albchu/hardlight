
#include "Wall.h"
#include <glm/glm.hpp>
#include <glm\gtx\rotate_vector.hpp>

Wall::Wall() {
}
	
Wall::Wall(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint new_texture) {
	type = UNDECLARED;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = new_texture;
	init_opengl();
}
	
Wall::~Wall() {
}

mat4 Wall::get_model_matrix() {
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y + 10.0f, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	float scaleFactor = 3.0f;

	model_matrix = scale(model_matrix, vec3(scaleFactor, 0.1f, scaleFactor));

	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));

	return model_matrix;
}
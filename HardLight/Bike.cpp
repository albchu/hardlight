#include "Bike.h"

Bike::Bike(PxRigidActor* init_actor, MeshData* init_mesh_data, const char* texture_file_path)
{
	type = BIKE;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = load_tga_texture(texture_file_path);
	init_opengl();
}

mat4 Bike::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	//cout << "Bike location" << glm::to_string(vec3(gPose.p.x, gPose.p.y, gPose.p.z)) << endl;
	model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));	// Flip the bike model around: This is a hack to get the correct physx bike lean
	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
	//model_matrix = rotate(model_matrix, rads * (axis.x), vec3(1, 0, 0));
	//model_matrix = rotate(model_matrix, rads * (axis.y), vec3(0, 1, 0));
	//model_matrix = rotate(model_matrix, (rads * normalize(axis.z)) * -5.0f, vec3(0, 0, 1));
	
	//model_matrix = scale(model_matrix, vec3(2.5,2.5,2.5));

	return model_matrix;
}

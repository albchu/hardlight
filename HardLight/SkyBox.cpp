#include "SkyBox.h"
#include <glm/glm.hpp>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;

SkyBox::SkyBox() {
	Entity();
}

SkyBox::SkyBox(PxRigidActor* init_actor, MeshData* init_mesh_data, const char* texture_file_path) 
{
	type = SKYBOX;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = load_tga_texture(texture_file_path);
	init_opengl();
}

mat4 SkyBox::get_model_matrix() {

	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));

	model_matrix = scale(model_matrix, vec3(3000.0, 3000.0, 3000.0));

	return model_matrix;
}
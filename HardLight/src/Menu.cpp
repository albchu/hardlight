
#include "Menu.h"
#include <glm\gtx\rotate_vector.hpp>

Menu::Menu() {
	type = UNDECLARED;
	draw_mode = GL_TRIANGLES;
	mesh_data = new MeshData();
	deleted = false;
}

Menu::Menu(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint new_texture) {
	type = UNDECLARED;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = new_texture;
	init_opengl();
	deleted = false;
}

Menu::~Menu() {

}

mat4 Menu::get_model_matrix() {
	
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	float Menuscale = 100.0f;

	model_matrix = scale(model_matrix, vec3(Menuscale, Menuscale, Menuscale));
	

	return model_matrix;
}
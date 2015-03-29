#include "SkyBox.h"
#include <glm/glm.hpp>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;

SkyBox::SkyBox() {
}

SkyBox::SkyBox(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint textID) 
{
	type = SKYBOX;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = textID;
	init_opengl();
}

SkyBox::~SkyBox() {
}

mat4 SkyBox::get_model_matrix() {

	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	float skyboxSize = 3000.0f;

	model_matrix = scale(model_matrix, vec3(skyboxSize, skyboxSize, skyboxSize));

	return model_matrix;
}
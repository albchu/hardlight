
#include "Menu.h"


//Menu::Menu() {
//	type = UNDECLARED;
//	draw_mode = GL_TRIANGLES;
//	mesh_data = new MeshData();
//	deleted = false;
//}

Menu::Menu(PxRigidActor* init_actor, Bike* new_bike) {
	type = MENU_PANEL;
	draw_mode = GL_TRIANGLES;
	bike = new_bike;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("plane.obj");
	texture = TextureMap::Instance()->getTexture("../data/images/HardLightTitle.tga");
	init_opengl();
	deleted = true;
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
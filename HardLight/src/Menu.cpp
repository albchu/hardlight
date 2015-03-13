
#include "Menu.h"


Menu::Menu(PxRigidActor* init_actor, Chassis* new_bike) {
	type = MENU_PANEL;
	draw_mode = GL_TRIANGLES;
	bike = new_bike;
	actor = init_actor;
	mesh_data = MeshMap::Instance()->getEntityMesh("menuPanel.obj");
	texture = TextureMap::Instance()->getTexture("../data/images/PausedTitle.tga");
	init_opengl();
	renderable = false;

	menu_offset_scalar = 9.0f;

	// Set the position of the panel to the bike's location
	actor->setGlobalPose(bike->get_actor()->getGlobalPose());
}

Menu::~Menu() {

}


// Returns the pxTransform of the tail with appropriate physx transform offsets
PxTransform Menu::getMenuTransform()
{
	// Update segment actor position
	vec3 location = bike->get_location();
	vec3 direction = bike->get_direction_vector();

	// Get a point that moves behind the direction vector
	location = location - (direction * vec3(menu_offset_scalar,menu_offset_scalar,menu_offset_scalar));

	// Offset the physx actor for the tail so it doesnt start in the exact same spot as its bike
	PxTransform bikeTransform = PxTransform(location.x, location.y + 8, location.z, bike->get_actor()->getGlobalPose().q);

	return bikeTransform;
}

mat4 Menu::get_model_matrix() {

	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = getMenuTransform();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	//model_matrix = translate(model_matrix, vec3(0, 0, -10));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);

	model_matrix = rotate(model_matrix, PxPi/2, vec3(0, 1, 0));
	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));

	float Menuscale = 0.2f;
	model_matrix = scale(model_matrix, vec3(Menuscale, Menuscale/2, Menuscale));

	return model_matrix;
}
#ifndef _MENU_H_
#define _MENU_H_

#include "Entity.h"

class Menu : public Entity {
private:
	
public:
	Menu();
	Menu(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint new_texture);
	~Menu();

	virtual mat4 get_model_matrix();
};

#endif
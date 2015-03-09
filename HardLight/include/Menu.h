#ifndef _MENU_H_
#define _MENU_H_

#include "Entity.h"
#include <glm\gtx\rotate_vector.hpp>
#include "Rendering\TextureMap.h"
#include "Vehicle/Bike.h"

class Menu : public Entity {
private:
	Bike* bike;
	float menu_offset_scalar;
public:
	Menu();
	Menu(PxRigidActor* init_actor, Bike* new_bike);
	~Menu();
	PxTransform getMenuTransform();
	virtual mat4 get_model_matrix();
};

#endif
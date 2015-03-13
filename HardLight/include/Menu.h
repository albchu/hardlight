#ifndef _MENU_H_
#define _MENU_H_

#include "Entity.h"
#include <glm\gtx\rotate_vector.hpp>
#include "Rendering\TextureMap.h"
#include "Vehicle/Chassis.h"

class Menu : public Entity {
private:
	Chassis* bike;
	float menu_offset_scalar;
public:
	Menu();
	Menu(PxRigidActor* init_actor, Chassis* new_bike);
	~Menu();
	PxTransform getMenuTransform();
	virtual mat4 get_model_matrix();
};

#endif
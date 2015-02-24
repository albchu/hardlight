#ifndef _BIKE_H
#define _BIKE_H

#include "Entity.h"
#include <PxPhysicsAPI.h>

class Bike : public Entity
{

public:
	Bike(PxRigidActor* actor, MeshData* meshdata, const char* texture):Entity(actor, meshdata, texture){};
	virtual mat4 get_model_matrix();
private:

};
#endif
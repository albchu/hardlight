#ifndef _BIKE_H
#define _BIKE_H

#include "Entity.h"
#include <PxPhysicsAPI.h>
#include <glm\gtx\rotate_vector.hpp>
#include <glm/glm.hpp>		// Used for vec3
#include "glm/gtx/string_cast.hpp"		// Used for to_string

using namespace glm;

class Bike : public Entity
{

public:
	Bike(PxRigidActor* actor, MeshData* meshdata, const char* texture):Entity(actor, meshdata, texture){};
	virtual mat4 get_model_matrix();
private:

};
#endif
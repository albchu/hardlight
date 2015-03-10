#ifndef _NEW_BIKE_H
#define _NEW_BIKE_H

// This is what i want the new bike to look like but i dont want to make too drastic of changes at one time immediately

#include "Entity.h"
//#include "TailWall.h"
#include "Bike.h"
#include "Controls/Controller.h"
#include "Camera.h"
//#include <PxPhysicsAPI.h>
//#include <vehicle/PxVehicleUtil.h>
//#include "../SnippetVehicleCommon/SnippetVehicleRaycast.h"
//#include "../SnippetVehicleCommon/SnippetVehicleFilterShader.h"
//#include "../SnippetVehicleCommon/SnippetVehicleTireFriction.h"
//#include "../SnippetVehicleCommon/SnippetVehicleCreate.h"
//
//#include <glm\gtx\rotate_vector.hpp>
//#include <glm/glm.hpp>		// Used for vec3
//#include "glm/gtx/string_cast.hpp"		// Used for to_string

using namespace glm;
using namespace std;

class newBike : public Entity
{

public:
	newBike(Bike* new_chassis);
	~newBike();

	BikeSubTypes get_subtype();
	void set_subtype(BikeSubTypes subtype);
	virtual void render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);	// Need to override to call each subentities respective elements

private:
	Controller* controller;
	Bike* chassis;
	Entity* front_tire;
	Entity* back_tire;
	Entity* tail_dispenser;
	Camera* camera; // Note: This field should only be set for player bike_manager
	BikeSubTypes subtype;
};
#endif
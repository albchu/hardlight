#ifndef _NEW_BIKE_H
#define _NEW_BIKE_H

// This is what i want the new bike to look like but i dont want to make too drastic of changes at one time immediately

#include "Entity.h"

//Powerups
//#include "Hold.h"
//#include "Instant.h"

//#include "TailWall.h"
//#include "Chassis.h"
#include "Controls/Player_Controller.h"
#include "Controls/Bot_Controller.h"
#include "Camera.h"
#include "../inih/cpp/INIReader.h"
#include "Vehicle/TailWall.h"

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

class Bike : public Entity
{

public:
	Bike(Chassis* init_chassis, BikeSubTypes init_subtype, INIReader* new_config, Controller* new_controller);
	~Bike();
	virtual void render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);	// Need to override to call each subentities respective elements
	BikeSubTypes get_subtype();
	void set_subtype(BikeSubTypes subtype);
	Chassis* get_chassis();
	TailWall* get_tail();
	Controller* get_controller();

	//typedef void (Hold::*HoldCallback)(Bike* bike);
	//void set_hold_powerup(HoldCallback powerup);
	//void execute_hold_powerup();

private:
	Controller* controller;
	Chassis* chassis;
	Entity* front_tire;
	Entity* back_tire;
	Entity* tail_dispenser;
	Camera* camera; // Note: This field should only be set for player bike_manager
	BikeSubTypes subtype;
	TailWall* tailwall;
	INIReader* config;
};
#endif
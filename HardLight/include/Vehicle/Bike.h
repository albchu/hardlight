#ifndef _BIKE_H
#define _BIKE_H

#include "Entity.h"

////Powerups
#include "Powerup/Hold.h"
#include "Powerup/Instant.h"
#include "Powerup/Powerup.h"

#include "Controls/Player_Controller.h"
#include "Controls/Bot_Controller.h"
#include "Camera.h"
#include "../inih/cpp/INIReader.h"
#include "Vehicle/TailWall.h"

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

	void set_hold_powerup(Powerup<Hold>::PowerCallback new_powerup);
	Powerup<Hold>::PowerCallback get_hold_powerup();
	void execute_hold_powerup();
	void execute_instant_powerup(Powerup<Instant>::PowerCallback new_powerup);

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
	Powerup<Hold>::PowerCallback powerup;
};
#endif
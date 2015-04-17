#ifndef _BIKE_H
#define _BIKE_H

#include "Entity.h"

////Powerups
#include "Powerup/Hold.h"
#include "Powerup/Instant.h"
#include "Powerup/Powerup.h"

#include "Controls/Player_Controller.h"
#include "Controls/Bot_Controller.h"
#include "Rendering/Viewports.h"
#include "Camera.h"
#include "../inih/cpp/INIReader.h"
#include "Vehicle/TailWall.h"



using namespace glm;
using namespace std;

class Bike : public Entity
{

public:
	int power;
	int left_contacts;
	int right_contacts;
	Bike(Chassis* init_chassis, BikeSubTypes init_subtype, INIReader* new_config, Controller* new_controller);
	virtual void render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);	// Need to override to call each subentities respective elements
	BikeSubTypes get_subtype();
	void set_subtype(BikeSubTypes subtype);
	Chassis* get_chassis();
	TailWall* get_tail();
	Controller* get_controller();
	PxVec3 get_gravity_up();
	void set_gravity_up(PxVec3 new_gravity_up);
	BikeID get_id();
	void set_id(BikeID id);

	void set_hold_powerup(Powerup<Hold>::PowerCallback new_powerup, int i);
	Powerup<Hold>::PowerCallback get_hold_powerup();
	void execute_hold_powerup();
	void execute_instant_powerup(Powerup<Instant>::PowerCallback new_powerup);

	// check the timers in powerup_timers
	void check_ghost_powerup(); 
	void check_super_saiyen_powerup();

	// update the score (on instant powerup pickup)
	int get_player_score();
	void update_player_score();
	void set_show_scoreboard(bool show_scoreboard);
	bool get_show_scoreboard();

	// contact management
	void add_left_contact();
	void add_right_contact();
	void remove_left_contact();
	void remove_right_contact();
	int lefts();
	int rights();

private:
	Controller* controller;
	Chassis* chassis;
	Entity* front_tire;
	Entity* back_tire;
	Entity* tail_dispenser;
	Camera* camera; // Note: This field should only be set for player bike_manager
	BikeID bikeID;
	BikeSubTypes subtype;
	TailWall* tailwall;
	INIReader* config;
	PowerupTimers* powerup_timers; // Variables needed for timed powerups
	Powerup<Hold>::PowerCallback powerup;
	int player_score;
	bool show_scoreboard;
};
#endif
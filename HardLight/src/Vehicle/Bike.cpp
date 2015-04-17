#include "Vehicle/Bike.h"

Bike::Bike(Chassis* init_chassis, BikeSubTypes init_subtype, INIReader* new_config, Controller* new_controller)
{
	config = new_config;
	chassis = init_chassis;
	type = BIKE;
	subtype = init_subtype;

	// Initialize tail
	tailwall = new TailWall(chassis, config);

	// Initialize controller 
	controller = new_controller;
	powerup = NULL;

	// Initialize powerup_timers
	powerup_timers = new PowerupTimers();
	powerup_timers->powerup_duration =(float)config->GetReal("powerup", "duration", 3.0);
	power = -1;

	// Initialize player score
	player_score = 0;
	
	// Initialize contact counters
	left_contacts = 0;
	right_contacts = 0;
	center_contacts = 0;
	turn = 0;

	// Initialize button flags
	x_toggle = false;
	y_toggle = false;
}

Chassis* Bike::get_chassis()
{
	return chassis;
}

TailWall* Bike::get_tail()
{
	return tailwall;
}


BikeSubTypes Bike::get_subtype()
{
	return subtype;
}

Controller* Bike::get_controller()
{
	return controller;
}

void Bike::set_subtype(BikeSubTypes new_subtype)
{
	subtype = new_subtype;
}

void Bike::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	chassis->render(projection_matrix,view_matrix,lightPos);
	tailwall->render(projection_matrix,view_matrix,lightPos);
}

void Bike::set_hold_powerup(Powerup<Hold>::PowerCallback new_powerup, int i)
{
	power = i;
	powerup = new_powerup;
}

void Bike::execute_hold_powerup()
{
	Hold hold;
	if(powerup != NULL)	// Only execute callback if its been set
	{
		(hold.*powerup)(chassis, tailwall, config, powerup_timers);
		powerup = NULL;	// Clear the powerup once its used
		cout << power << endl;
		power = -1;
	}
}


void Bike::execute_instant_powerup(Powerup<Instant>::PowerCallback instant_powerup)
{
	Instant instant;
	(instant.*instant_powerup)(chassis, tailwall, config, powerup_timers);
	update_player_score();
}

Powerup<Hold>::PowerCallback Bike::get_hold_powerup()
{
	return powerup;
}

PxVec3 Bike::get_gravity_up()
{
	return get_chassis()->get_gravity_up();
}

void Bike::set_gravity_up(PxVec3 new_gravity)
{
	get_chassis()->set_gravity_up(new_gravity);
}

void Bike::check_ghost_powerup()
{
	// Calculate time difference between current time and powerup activation time
	float time_difference = (float)(clock() - powerup_timers->ghost_timer) / CLOCKS_PER_SEC;
	if(powerup_timers->using_ghost == true && time_difference > powerup_timers->powerup_duration)
	{
		// Reset ghost_timer to zero; set using_ghost flag to false
		powerup_timers->ghost_timer = 0;
		powerup_timers->using_ghost = false;

		// Deactivate ghost ability
		chassis->set_invincible(false);
		chassis->set_texture(chassis->get_regular_texture());
	}
}

void Bike::check_super_saiyen_powerup()
{
	// Calculate time difference between current time and powerup activation time
	float time_difference = (float)(clock() - powerup_timers->super_saiyen_timer) / CLOCKS_PER_SEC;
	if(powerup_timers->using_super_saiyen && time_difference > powerup_timers->powerup_duration)
	{
		// Reset super_saiyen_timer to zero; set using_super_saiyen to false
		powerup_timers->super_saiyen_timer = 0;
		powerup_timers->using_super_saiyen = false;

		// Deactivate super saiyen ability
		tailwall->set_width((float)config->GetReal("tail", "width", 1));
		tailwall->set_height((float)config->GetReal("tail", "height", 1));
	}
}

BikeID Bike::get_id() {
	return bikeID;
}

void Bike::set_id(BikeID id) {
	bikeID = id;
}

int Bike::get_player_score()
{
	return player_score;
}

void Bike::update_player_score()
{
	player_score++;
}

void Bike::set_show_scoreboard(bool show_scoreboard)
{
	this->show_scoreboard = show_scoreboard;
}

bool Bike::get_show_scoreboard()
{
	return show_scoreboard;
}

void Bike::add_left_contact()
{
	left_contacts++;
}

void Bike::add_right_contact()
{
	right_contacts++;
}

void Bike::add_center_contact()
{
	center_contacts++;
}

void Bike::remove_left_contact()
{
	if (left_contacts > 0)
		left_contacts--;
}

void Bike::remove_right_contact()
{
	if (right_contacts > 0)
		right_contacts--;
}

void Bike::remove_center_contact()
{
	if (center_contacts > 0)
		center_contacts--;
}

int Bike::lefts()
{
	return left_contacts;
}

int Bike::rights()
{
	return right_contacts;
}

int Bike::centers()
{
	return center_contacts;
}

int Bike::get_turn()
{
	if (center_contacts == 0)
	{
		turn = 0;
	}
	if (turn == -1)
	{
		if (left_contacts == 0)
			turn = 0;
	}
	if (turn == 1)
	{
		if (right_contacts == 0)
			turn = 0;
	}
	if (turn == 0)
	{
		if (left_contacts > right_contacts)
		{
			turn = -1;
		}
		else if (right_contacts > left_contacts)
		{
			turn = 1;
		}
	}
	return turn;
}void Bike::set_x_toggle(bool x_toggle)
{
	this->x_toggle = x_toggle;
}

bool Bike::get_x_toggle()
{
	return x_toggle;
}

void Bike::set_y_toggle(bool y_toggle)
{
	this->y_toggle = y_toggle;
}

bool Bike::get_y_toggle()
{
	return y_toggle;
}

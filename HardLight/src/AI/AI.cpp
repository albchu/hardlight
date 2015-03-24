#include "AI/AI.h"


AI::AI(BikeManager* init_manager, SoundMixer* init_sfxMix)
{
	bike_manager = init_manager;
	sfxMix = init_sfxMix;
	//	keyMappings = init_keyMappings;
}

//void AI::notify(SDL_Keycode key)
//{
//	keyPresses.push_back(key);
//}

// Sets the callbacks for controlling the vehicles
void AI::update_bikes()
{
	for(unsigned int i = 0; i < bike_manager->get_all_bikes().size(); i++)
	{
		Bike* bikeX = bike_manager->get_all_bikes()[i];
		Controller* controllableX = bikeX->get_controller();
		if(controllableX->get_chassis()->is_renderable() && bikeX->get_subtype() == BOT_BIKE)
		{

			vec3 directionX = controllableX->get_chassis()->get_direction_vector();
			vec3 positionX = controllableX->get_chassis()->get_location();
			float shortest_distance = NULL;
			vec3 target_location = directionX;	// If no better direction is found, the bike will continue going straight forward
			for(unsigned int j = 0; j < bike_manager->get_all_bikes().size(); j++)	// Try and find a better target location to go to
			{
				Bike* bikeY = bike_manager->get_all_bikes()[j];
				Controller* controllableY = bikeY->get_controller();
				// Allow all vehicles to see each other
				if(controllableY->get_chassis()->is_renderable() && i != j)	// Only perform calculation if both bike_manager arnt deleted and arnt the same bike
				{
					vec3 directionY = controllableX->get_chassis()->get_direction_vector();
					vec3 positionY = controllableX->get_chassis()->get_location();

					//Find direction vector from bikeX to bikeY
					vec3 xy_direction = positionY - positionX;

					//Determine whether this point is in the view of bikeX
					float angle = glm::angle(xy_direction, directionX);

					// Only determine distance between the bike_manager if bikeX can see bikeY
					if(angle < Common::FORTY_FIVE_DEGREES_RADS)
					{
						float XY_distance = glm::distance(positionY, positionX); // Find distance between the two bike_manager
						if(shortest_distance == NULL || XY_distance < shortest_distance)
						{
							shortest_distance = XY_distance;
							target_location = positionY;
						}
					}
				}
			}
			float dot1 = directionX.x*target_location.x + directionX.z*target_location.z;
			float det1 = directionX.x*target_location.z - directionX.z*target_location.x;
			float angle = -atan2(det1, dot1);

			// Go to target location
			controllableX->set_motion(&Controller::forward);
			controllableX->set_steering(&Controller::steer);
			//cout << "steer degrees: " << position << endl;
			controllableX->set_direction(angle/PxPi);
		}
	}
}

void AI::update_bikes(vec3 pickup)
{
	for(unsigned int i = 0; i < bike_manager->get_all_bikes().size(); i++)
	{
		Bike* bikeX = bike_manager->get_all_bikes()[i];
		Controller* controllableX = bikeX->get_controller();
		if(controllableX->get_chassis()->is_renderable())
		{
			if(bikeX->get_subtype() == BOT_BIKE)
			{
				vec3 current_direction = normalize(controllableX->get_chassis()->get_direction_vector());
				vec3 current_postion = controllableX->get_chassis()->get_location();
				vec3 desired_direction = normalize(pickup - current_postion);
				float dot1 = current_direction.x*desired_direction.x + current_direction.z*desired_direction.z;
				float det1 = current_direction.x*desired_direction.z - current_direction.z*desired_direction.x;
				float angle = -atan2(det1, dot1);
				// Go to target location
				controllableX->set_motion(&Controller::forward);
				controllableX->set_steering(&Controller::steer);
				controllableX->set_direction(angle/PxPi);
				controllableX->set_acceleration(controllableX->get_max_acceleration());
			}
			else if(bikeX->get_subtype() == PLAYER_BIKE)
			{
				update_player(bikeX);
			}
		}
		//else {
		//	bike_manager->kill_bike(controllableX->get_chassis());
		//}
	}
}

void AI::move_bikes()
{
	for(Bike* bike: bike_manager->get_all_bikes())
	{
		if(bike->get_controller()->get_chassis()->is_renderable() && bike->get_controller()->callbacks_set())
		{
			bike->get_controller()->execute_motion();
			bike->get_controller()->execute_steering();
		}
	}
}

// Get all input for the player and perform based on that. Note: Could not do keyboard presses this way
void AI::update_player(Bike* bike)
{
	if(((Player_Controller*)bike->get_controller())->get_controller() != NULL)
		update_controller(bike);

}

// Get all controller input and set the proper callbacks
void AI::update_controller(Bike* bike)
{
	Player_Controller* player = ((Player_Controller*)bike->get_controller());
	int LeftX = SDL_GameControllerGetAxis(player->get_controller(), SDL_CONTROLLER_AXIS_LEFTX);
	int RightX = SDL_GameControllerGetAxis(player->get_controller(), SDL_CONTROLLER_AXIS_RIGHTX);
	int RightY = SDL_GameControllerGetAxis(player->get_controller(), SDL_CONTROLLER_AXIS_RIGHTY);
	float accel = player->get_min_acceleration(); // Default acceleration to minimum if non is given
	PxReal steer = 0.0;

	if (LeftX < -(player->get_dead_zone()) || LeftX > player->get_dead_zone())
	{
		steer = (LeftX)/(-32768.0f); //the axis are inverted on the controller
	}

	if(SDL_GameControllerGetAxis(player->get_controller(), SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0)
	{
		accel = SDL_GameControllerGetAxis(player->get_controller(), SDL_CONTROLLER_AXIS_TRIGGERRIGHT)/32768.0f;
		//player->rumble(0.15, 15);
		// Cap the speed into a specific range
		if (accel < player->get_min_acceleration())
			accel = player->get_min_acceleration();
		if (accel > player->get_max_acceleration())
			accel = player->get_max_acceleration();
	}

	// Trigger powerup
	if(SDL_GameControllerGetButton(player->get_controller(), SDL_CONTROLLER_BUTTON_A))
	{
		if(bike->get_hold_powerup() != NULL)
			//sfxMix->PlaySoundEffect("sfxPowerupNone");
		//else
		{
			sfxMix->PlaySoundEffect("sfxPowerupActivated");
			bike->execute_hold_powerup();
			player->rumble(1.0, 70);

		}
	}
		

	if(SDL_GameControllerGetButton(player->get_controller(), SDL_CONTROLLER_BUTTON_B))
		sfxMix->PlaySoundEffect("sfxIntro");

	player->set_motion(&Controller::forward);
	player->set_steering(&Controller::steer);
	player->set_direction(steer);
	player->set_acceleration(accel);
}

// Commands feel delayed, abandoning this approach
//void AI::update_keyboard(Player_Controller* player)
//{
//	KeyMapping mapping = player->get_key_controls();
//	//float accel = player->get_min_acceleration(); // Default acceleration to minimum if non is given
//	//PxReal steer = 0.0;
//
//	for(SDL_Keycode keyPressed: keyPresses)
//	{
//		if(keyPressed == mapping.forward)
//			player->set_acceleration(player->get_max_acceleration());
//
//		else if(keyPressed == mapping.backward)
//			player->set_acceleration(player->get_min_acceleration());
//
//		else if(keyPressed == mapping.left)
//			player->set_direction(1.0);
//
//		else if(keyPressed == mapping.right)
//			player->set_direction(-1.0);
//		//if(keyPressed == mapping.camera_left)
//
//		//if(keyPressed == mapping.camera_right)
//
//		//if(keyPressed == mapping.use_powerup)
//
//	}
//	//cout << "Acceleration: " << accel << endl;
//	//cout << "Steer: " << get_direction() << endl;
//
//	player->set_motion(&Controller::forward);
//	player->set_steering(&Controller::steer);
//	//player->set_direction(steer);
//	//player->set_acceleration(accel);
//}

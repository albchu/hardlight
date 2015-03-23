#include "Controls/Player_Controller.h"

Player_Controller::Player_Controller(Chassis* new_chassis, SDL_GameController* new_sdl_controller)
{
	init_values();
	chassis = new_chassis;
	sdl_controller = new_sdl_controller;
	init_rumble();
}

Player_Controller::~Player_Controller()
{
	cout << "CLOSING CONTROLLERS" << endl;
	//Close game controller with haptics 
	if(sdl_controller != NULL)
	{
		SDL_HapticClose( gControllerHaptic );
		//SDL_JoystickClose(SDL_GameControllerGetJoystick(sdl_controller));	// Apparently sdl quit cant allow this to happen explicitly
	}

}

// If the controller isnt null, we set it up for rumblin
void Player_Controller::init_rumble()
{
	if(sdl_controller != NULL)
	{
		//Get controller haptic device 
		gControllerHaptic = SDL_HapticOpenFromJoystick(SDL_GameControllerGetJoystick(sdl_controller)); 
		if( gControllerHaptic == NULL ) 
		{
			printf( "Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError() );
		} else 
		{ 
			//Get initialize rumble 
			if( SDL_HapticRumbleInit( gControllerHaptic ) < 0 ) 
			{ 
				printf( "Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError() ); 
			} 
		}
	}
}

void Player_Controller::rumble(float strength, int duration)
{
	//Play rumble at 75% strenght for 500 milliseconds 
	if( gControllerHaptic != NULL && SDL_HapticRumblePlay( gControllerHaptic, strength, duration ) != 0 ) 
	{
		printf( "Warning: Unable to play rumble! %s\n", SDL_GetError() ); 
	}
}

Player_Controller::Player_Controller(Chassis* new_chassis, KeyMapping init_keys)
{
	init_values();
	chassis = new_chassis;
	key_controls = init_keys;
}

void Player_Controller::init_values()
{
	cout << "Player controller has been set!" << endl;

	sdl_controller = NULL;
	max_acceleration = 1.0;
	min_acceleration = 0.5;
	acceleration = min_acceleration;
	direction = 0.0;
	deadZone = 8000;
	steeringMethod = NULL;
	motionMethod = NULL;
}

SDL_GameController* Player_Controller::get_controller()
{
	return sdl_controller;
}

int Player_Controller::get_dead_zone()
{
	return deadZone;
}

KeyMapping Player_Controller::get_key_controls()
{
	return key_controls;
}


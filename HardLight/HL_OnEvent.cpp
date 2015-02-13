//==============================================================================
#include "HardLight.h"
//==============================================================================

const int deadzone = 8000;

void HardLight::OnEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
	case SDL_QUIT:
		running = false;
		break;

	case SDL_KEYDOWN:
		switch (Event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			running = false;
			break;
		case SDLK_a:
			left = 1;
			break;
		case SDLK_d:
			right = 1;
			break;
		case SDLK_s:
			back = 1;
			break;
		case SDLK_w:
			forward = 1;
			break;
		case SDLK_LSHIFT:
			speed *= fast;
			break;
		case SDLK_UP:
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
			gVehicleInputData.setAnalogAccel(1.0f);
			break;
		case SDLK_DOWN:
			gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
			gVehicleInputData.setAnalogAccel(1.0f);
			break;
		case SDLK_LEFT:
			gVehicleInputData.setAnalogSteer(1.0f);
			break;
		case SDLK_RIGHT:
			gVehicleInputData.setAnalogSteer(-1.0f);
			break;
		} // end key_down
		break;

	case SDL_KEYUP:
		switch (Event->key.keysym.sym)
		{
		case SDLK_a:
			left = 0;
			break;
		case SDLK_d:
			right = 0;
			break;
		case SDLK_s:
			back = 0;
			break;
		case SDLK_w:
			forward = 0;
			break;
		case SDLK_LSHIFT:
			speed /= fast;
			break;
		case SDLK_UP:
			gVehicleInputData.setAnalogAccel(0.0f);
			break;
		case SDLK_DOWN:
			gVehicleInputData.setAnalogAccel(0.0f);
			break;
		case SDLK_LEFT:
			gVehicleInputData.setAnalogSteer(0.0f);
			break;
		case SDLK_RIGHT:
			gVehicleInputData.setAnalogSteer(0.0f);
			break;
		} // end key_up
		break;

	case SDL_MOUSEMOTION:

		break;
	case SDL_CONTROLLERAXISMOTION:
		int LeftX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		if (LeftX < -deadzone){
			left = (LeftX+deadzone)/(-24768.0);
		}else if(LeftX > deadzone){
			right = (LeftX-deadzone)/(24768.0);
		}else{
			left = right = 0;
		}
		int LeftY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
		if (LeftY < -deadzone){		//up on joystick
			back = (LeftY+deadzone)/(-24768.0);
		}else if(LeftY > deadzone){ //down on joystick
			forward = (LeftY-deadzone)/(24768.0);
		}else{
			forward = back = 0;
		}
		//printf("Left X = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX));
		//printf("Y = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY));
		////Right Stick
		//printf("Right X = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX));
		//printf("Y = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY));
		////trigger buttons
		//printf("Left Trigger = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
		//printf("Right Trigger = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
		break;
	} // end type
}

//==============================================================================

//==============================================================================
#include "HardLight.h"
//==============================================================================

const int deadZone = 8000;

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
			left = 1.0f;
			break;
		case SDLK_d:
			right = 1.0f;
			break;
		case SDLK_s:
			back = 1.0f;
			break;
		case SDLK_w:
			forward = 1.0f;
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
			left = 0.0f;
			break;
		case SDLK_d:
			right = 0.0f;
			break;
		case SDLK_s:
			back = 0.0f;
			break;
		case SDLK_w:
			forward = 0.0f;
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
		int RightX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
		int RightY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
			if (LeftX < -deadZone || LeftX > deadZone){
				gVehicleInputData.setAnalogSteer((LeftX)/(-32768.0f));//the axis are inverted on the controller

			}else{
				gVehicleInputData.setAnalogSteer(0.0f);
			}
			if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 0){
				gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
				gVehicleInputData.setAnalogAccel(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT)/32768.0f);
			}else if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0){
				gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
				gVehicleInputData.setAnalogAccel((SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)/32768.0f));
			}else{
				gVehicleInputData.setAnalogAccel(0.0f);
			}
			if(RightX < -deadZone){
				left =(RightX)/(-32768.0f);
			}else if(RightX > deadZone){
				left = (RightX)/(-32768.0f);
			}else {
				left = right = 0.0f;
			}		
			if(RightY > deadZone){
				forward = (RightY)/(-32768.0f);
			}else if(RightY < -deadZone){
				forward = (RightY)/(-32768.0f);
			}else{
				forward = back = 0.0f;
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

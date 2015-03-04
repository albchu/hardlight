//==============================================================================
#include "HardLight.h"
//==============================================================================

const int deadZone = 8000;

void HardLight::OnEvent(SDL_Event* Event)
{
	if (Event->type == SDL_QUIT)
		running = false;

	if (bikes->get_player_bikes().size() > 0)
	{
		Bike* bike = bikes->get_player_bikes()[0];
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
				bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
				bike->getInputData().setAnalogAccel(1.0f);
				break;
			case SDLK_DOWN:
				bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
				bike->getInputData().setAnalogAccel(1.0f);
				break;
			case SDLK_LEFT:
				bike->getInputData().setAnalogSteer(1.0f);
				break;
			case SDLK_RIGHT:
				bike->getInputData().setAnalogSteer(-1.0f);
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
				bike->getInputData().setAnalogAccel(0.0f);
				break;
			case SDLK_DOWN:
				bike->getInputData().setAnalogAccel(0.0f);
				break;
			case SDLK_LEFT:
				bike->getInputData().setAnalogSteer(0.0f);
				break;
			case SDLK_RIGHT:
				bike->getInputData().setAnalogSteer(0.0f);
				break;
			} // end key_up
			break;

		case SDL_MOUSEMOTION:

			break;

		case SDL_CONTROLLERBUTTONDOWN:
			switch (Event->cbutton.button)
			{
			case SDL_CONTROLLER_BUTTON_A: // A button
				sfxMix.PlaySoundEffect("sfxEngine");
				break;
			case SDL_CONTROLLER_BUTTON_B: // B button
				sfxMix.PlaySoundEffect("sfxExplosion");
				break;
			case SDL_CONTROLLER_BUTTON_X: // X button
				sfxMix.PlaySoundEffect("sfxIntro");
				break;
			case SDL_CONTROLLER_BUTTON_Y: // Y button
				sfxMix.PlaySoundEffect("sfxItemPickUp");
				break;
			case SDL_CONTROLLER_BUTTON_START: // START button
				scene = MENU;
				sfxMix.PlaySoundEffect("sfxItemUsed");
				break;
			case SDL_CONTROLLER_BUTTON_BACK:
				for(Bike* bike : bikes->get_bot_bikes()) {
					pxAgent->get_scene()->removeActor(*bike->get_actor(), false);
					bikes->kill_bike(bike);
				}
				BuildScene();
				break;
			}
			break;

		case SDL_CONTROLLERAXISMOTION:
			int LeftX = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_LEFTX);
			int RightX = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_RIGHTX);
			int RightY = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_RIGHTY);
			if (LeftX < -deadZone || LeftX > deadZone){
				bike->getInputData().setAnalogSteer((LeftX)/(-32768.0f));//the axis are inverted on the controller

			}else{
				bike->getInputData().setAnalogSteer(0.0f);
			}
			if(SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 0){
				bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
				bike->getInputData().setAnalogAccel(SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERLEFT)/32768.0f);
			}else if(SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0){
				bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
				bike->getInputData().setAnalogAccel((SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERRIGHT)/32768.0f));
			}else{
				bike->getInputData().setAnalogAccel(0.0f);
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
			break;
		} // end type
	}
}

//==============================================================================

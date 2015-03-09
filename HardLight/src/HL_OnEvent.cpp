//==============================================================================
#include "HardLight.h"
//==============================================================================

const int deadZone = 8000;

void HardLight::OnEvent(SDL_Event* Event)
{
	if (Event->type == SDL_QUIT)
		running = false;

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
		case SDLK_SPACE:
			//scene = PAUSE;
			//gui.loadMenu("Paused.txt", pxAgent->get_physics());
			menu->toggle_renderable();	// Toggle menu panel from being rendered
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
		} // end key_up
		break;
	case SDL_CONTROLLERBUTTONDOWN:
		switch (Event->cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A: // A button
			//sfxMix.PlaySoundEffect("sfxExplosion", 350.0f, 0);
			powerup->setPowerType(JUMP);
			if(powerup->usePowerup() == 1)
				sfxMix.PlaySoundEffect("sfxItemUsed");
			else
				sfxMix.PlaySoundEffect("sfxIntro");
			break;
		case SDL_CONTROLLER_BUTTON_B: // B button
			sfxMix.PlaySoundEffect("sfxExplosion", 10.0f, 0);
			break;
		case SDL_CONTROLLER_BUTTON_X: // X button
			//sfxMix.PlaySoundEffect("sfxIntro");
			powerup->setPowerType(EXTENDTAIL);
			if(powerup->usePowerup() == 1)
				sfxMix.PlaySoundEffect("sfxItemUsed");
			else
				sfxMix.PlaySoundEffect("sfxIntro");
			break;
		case SDL_CONTROLLER_BUTTON_Y: // Y button
			//sfxMix.PlaySoundEffect("sfxItemPickUp");
			powerup->setPowerType(INVINCIBLE);
			if(powerup->usePowerup() == 1)
				sfxMix.PlaySoundEffect("sfxItemUsed");
			else
				sfxMix.PlaySoundEffect("sfxIntro");
			break;
		case SDL_CONTROLLER_BUTTON_START: // START button
			//scene = PAUSE;
			//gui.loadMenu("Paused.ini", pxAgent->get_physics());

			for(Bike* i : bikes->get_player_bikes()) {
				menu->toggle_renderable();
			}

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
		int RightX = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_RIGHTX);
		int RightY = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_RIGHTY);
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

	if (bikes->get_player_bikes().size() > 0)
	{
		Bike* bike = bikes->get_player_bikes()[0];
		switch (Event->type)
		{
		case SDL_KEYDOWN:
			switch (Event->key.keysym.sym)
			{
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
		case SDL_CONTROLLERAXISMOTION:
			int LeftX = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_LEFTX);
			if (LeftX < -deadZone || LeftX > deadZone){
				//bike->getInputData().setAnalogSteer((LeftX)/(-32768.0f)); //the axis are inverted on the controller
				bike->adaptiveSteering(LeftX); //the axis are inverted on the controller
			}else{
				bike->getInputData().setAnalogSteer(0.0f);
			}
			if(SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 0){
				bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
				bike->getInputData().setAnalogAccel(SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERLEFT)/32768.0f);
			}else if(SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0){
				bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
				bike->getInputData().setAnalogAccel((SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_TRIGGERRIGHT)/32768.0f));
				//PxVec3 temp = bike->getVehicle4W()->getRigidDynamicActor()->getLinearVelocity();
				//std::cout << "Linear Velocity: " << temp.x << " " << temp.y << " " << temp.z << " " << std::endl;
			}else{
				bike->getInputData().setAnalogAccel(0.0f);
			}
			break;
		} // end type
	}
}

//==============================================================================
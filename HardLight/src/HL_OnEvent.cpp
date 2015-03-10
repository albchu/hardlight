//==============================================================================
#include "HardLight.h"
//==============================================================================

const int deadZone = 8000;
const float minAccel = 0.8f;

void HardLight::OnEvent(SDL_Event* Event)
{
	Chassis* bike = NULL;
	if (bike_manager->get_player_bikes().size() > 0)
		bike = bike_manager->get_player_bikes()[0];

	switch (Event->type)
	{
	case SDL_QUIT:
		running = false;
		break;

	case SDL_KEYDOWN:
		//overMind->notify(Event->key.keysym.sym);
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
			if (bike != NULL) bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
			if (bike != NULL) bike->getInputData().setAnalogAccel(1.0f);
			break;
		case SDLK_DOWN:
			//if (bike != NULL) bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
			if (bike != NULL) bike->getInputData().setAnalogAccel(1.0f);
			break;
		case SDLK_LEFT:
			if (bike != NULL) bike->getInputData().setAnalogSteer(1.0f);
			break;
		case SDLK_RIGHT:
			if (bike != NULL) bike->getInputData().setAnalogSteer(-1.0f);
			break;
		case SDLK_SPACE:
			if(scene == PAUSE)
				scene = GAME;
			else if(scene == GAME)
				scene = PAUSE;
			menu->toggle_renderable();	// Toggle menu panel from being rendered
			break;
		case SDLK_r:
			reset();
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
			if (bike != NULL) bike->getInputData().setAnalogAccel(minAccel);
			break;
		case SDLK_DOWN:
			if (bike != NULL) bike->getInputData().setAnalogAccel(0.0f);
			break;
		case SDLK_LEFT:
			if (bike != NULL) bike->getInputData().setAnalogSteer(0.0f);
			break;
		case SDLK_RIGHT:
			if (bike != NULL) bike->getInputData().setAnalogSteer(0.0f);
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
		case SDL_CONTROLLER_BUTTON_X: // X button
			//sfxMix.PlaySoundEffect("sfxIntro");
			powerup->setPowerType(EXTENDTAIL);
			if(powerup->usePowerup() == 1);
			//sfxMix.PlaySoundEffect("sfxItemUsed");
			//else
			//sfxMix.PlaySoundEffect("sfxIntro");
			break;
		case SDL_CONTROLLER_BUTTON_Y: // Y button
			//sfxMix.PlaySoundEffect("sfxItemPickUp");
			powerup->setPowerType(INVINCIBLE);
			if(powerup->usePowerup() == 1);
			//sfxMix.PlaySoundEffect("sfxItemUsed");
			//else
			//sfxMix.PlaySoundEffect("sfxIntro");
			break;
		case SDL_CONTROLLER_BUTTON_START: // START button
			if(scene == PAUSE)
				scene = GAME;
			else if(scene == GAME)
				scene = PAUSE;

			for(Chassis* i : bike_manager->get_player_bikes()) {
				menu->toggle_renderable();
			}
			sfxMix.PlaySoundEffect("sfxPause");
			break;
		case SDL_CONTROLLER_BUTTON_BACK:
			reset();
			break;
		}
		break; // end SDL_CONTROLLERBUTTONDOWN

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
}

void HardLight::reset()
{
	if(scene == PAUSE)
		scene = GAME;
	for(Chassis* bike : bike_manager->get_all_bikes()) {
		pxAgent->get_scene()->removeActor(*bike->get_actor(), false);
		bike_manager->kill_bike(bike);
	}
	bike_manager->clear_controllers();
	pxAgent->cleanup();
	pxAgent = new PhysxAgent(config, this);
	world.clear();
	bike_manager = new BikeManager(&world, config);
	overMind = new AI(bike_manager);//, keyMappings);
	BuildScene();
}

//==============================================================================
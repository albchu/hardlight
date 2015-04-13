//==============================================================================
#include "HardLight.h"
//==============================================================================

const int deadZone = 8000;
const float minAccel = 0.85f;

void HardLight::OnEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
	case SDL_QUIT:
		running = false;
		break;

	case SDL_KEYDOWN:
		//overMind->notify(Event->key.keysym.sym);

		switch (Event->key.keysym.sym)
		{
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
		case SDLK_e:
			sfxMix.ClipFrom("../data/Audio/taunts/");
			break;
		case SDLK_LSHIFT:
			speed *= fast;
			break;

		//case SDLK_l:
		//	menu_active = !menu_active;	// toggle the menu to active
		//	break;
		case SDLK_DOWN:
			menuManager->down();
			break;

		case SDLK_UP:
			menuManager->up();
			break;

		case SDLK_LEFT:
			menuManager->left();
			break;

		case SDLK_RIGHT:
			menuManager->right();
			break;

		case SDLK_RETURN:
			menuManager->select();
			break;

		case SDLK_ESCAPE:
			menuManager->set_current_menu(pauseMenu);
			menu_active = true;
			break;

		case SDLK_p:
			toggle_pause();
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
		} // end key_up
		break;
	case SDL_CONTROLLERBUTTONDOWN:
		switch (Event->cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_START: // START button
			toggle_pause();

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
	if(scene == PAUSE || scene == GAME_OVER)
		scene = GAME;
	for(Bike* bike : bike_manager->get_all_bikes()) {
		pxAgent->get_scene()->removeActor(*bike->get_chassis()->get_actor(), false);
		bike_manager->kill_bike(bike);
	}
	for(Viewports::Viewport port : viewports)
		port.message = "";
	bike_manager->clear_controllers();
	pxAgent->cleanup();
	pxAgent = new PhysxAgent(config, this);
	bikesToKill.clear();
	world.clear();
	bike_manager = new BikeManager(&world, config, pxAgent);
	overMind = new AI(bike_manager, &sfxMix);//, keyMappings);
	powerup_manager = new PowerupManager(&world, config, pxAgent, &sfxMix);
	BuildScene();
}

void HardLight::toggle_pause()
{
	//sfxMix.PlaySoundEffect("sfxExplosion");
	if(scene == PAUSE)
	{
		sfxMix.PlaySoundEffect("sfxUnpaused");
		scene = GAME;
	}
	else if(scene == GAME)
	{
		sfxMix.PlaySoundEffect("sfxPaused");
		scene = PAUSE;
	}
}

//==============================================================================
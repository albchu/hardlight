//==============================================================================
#include "HardLight.h"
//==============================================================================

const int deadZone = 30000;
const float minAccel = 0.85f;
bool xMoved = false;
bool yMoved = false;

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
		case SDLK_DOWN:
			// Only apply this command if the menu is active
			if(menu_active)
				menuManager->down();
			break;

		case SDLK_UP:
			// Only apply this command if the menu is active
			if(menu_active)
				menuManager->up();
			break;

		case SDLK_LEFT:
			// Only apply this command if the menu is active
			if(menu_active)
				menuManager->left();
			break;

		case SDLK_RIGHT:
			// Only apply this command if the menu is active
			if(menu_active)
				menuManager->right();
			break;

		case SDLK_RETURN:
			// Only apply this command if the menu is active
			if(menu_active)
				menuManager->select();
			break;

		case SDLK_ESCAPE:	
			// Only apply this command if the game has been loaded 
			if(game_launched)
			{
				menuManager->set_current_menu(pauseMenu);
				menu_active = true;
			}
			break;

		case SDLK_p:
			toggle_pause();
			break;
		case SDLK_r:
			reset();
			break;		
		} // end key_down
		break;

	case SDL_CONTROLLERBUTTONDOWN:
		switch (Event->cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_START: // START button
			//toggle_pause();
			// Only apply this command if the game has been loaded 
			if(game_launched)
			{
				menuManager->set_current_menu(pauseMenu);
				menu_active = true;
			}
			break;
		//case SDL_CONTROLLER_BUTTON_BACK:
		//	reset();
		//	break;
		case SDL_CONTROLLER_BUTTON_A:
			if(menu_active)
				menuManager->select();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			if(menu_active)
				menuManager->up();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			if(menu_active)
				menuManager->left();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			if(menu_active)
				menuManager->down();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			if(menu_active)
				menuManager->right();
			break;
		}
		break; // end SDL_CONTROLLERBUTTONDOWN

	case SDL_CONTROLLERAXISMOTION:
		if(menu_active)
		{
			int LeftX = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_LEFTX);
			int LeftY = SDL_GameControllerGetAxis(controllers[0], SDL_CONTROLLER_AXIS_LEFTY);
			if(LeftX < -deadZone)
			{
				if (!xMoved)
				{
					menuManager->left();
					xMoved=true;
				}
			}
			else if(LeftX > deadZone)
			{
				if (!xMoved)
				{
					menuManager->right();
					xMoved=true;
				}
			}
			else
			{
				xMoved=false;
			}		
			if(LeftY > deadZone)
			{
				if (!yMoved)
				{
					menuManager->down();
					yMoved=true;
				}
			}
			else if(LeftY < -deadZone)
			{
				if (!yMoved)
				{
					menuManager->up();
					yMoved=true;
				}
			}
			else
			{
				yMoved = false;
			}
		}
		break; // end SDL_CONTROLLERAXISMOTION
	} // end type
}

void HardLight::reset()
{
	if(scene == PAUSE || scene == GAME_OVER)
		scene = GAME;
	for(Bike* bike : bike_manager->get_all_bikes()) {
		bike_manager->kill_bike(bike);
	}
	for(Viewports::Viewport port : viewports)
	{
		port.message = "";
		delete port.camera;
	}
	viewports.clear();
	bike_manager->release();
	pxAgent->cleanup();
	pxAgent = new PhysxAgent(config, this);
	bikesToKill.clear();
	world.clear();
	bike_manager = new BikeManager(&world, config, pxAgent);
	overMind = new AI(bike_manager, &sfxMix, config);//, keyMappings);
	powerup_manager = new PowerupManager(&world, config, pxAgent, &sfxMix);
	bikePowerupPairs.clear();
	BuildScene();
	OnLoop();
}

void HardLight::toggle_pause()
{
	if(scene == PAUSE)
	{
		sfxMix.PlaySoundEffect("sfxUnpaused");
		scene = GAME;
	}
	else if(scene == GAME)
	{
		sfxMix.PlaySoundEffect("sfxPaused");
		scene = PAUSE;
		if(game_launched)
		{
			menuManager->set_current_menu(pauseMenu);
			menu_active = true;
		}
	}
}

//==============================================================================
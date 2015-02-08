//==============================================================================
#include "HardLight.h"
//==============================================================================
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
		} // end key_up
		break;

	case SDL_MOUSEMOTION:

		break;
	case SDL_CONTROLLERAXISMOTION:
		printf("Left X = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX));
		printf("Y = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY));
		//Right Stick
		printf("Right X = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX));
		printf("Y = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY));
		//trigger buttons
		printf("Left Trigger = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
		printf("Right Trigger = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
		break;
	} // end type
}

//==============================================================================

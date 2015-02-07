//==============================================================================
#include "HardLight.h"
const int DEAD_ZONE = 8000;
//==============================================================================
void HardLight::OnEvent(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT) {
        running = false;
	}else if(Event->type == SDL_CONTROLLERAXISMOTION){
						//Left Stick
						printf("Left X = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX));
						printf("Y = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY));
						//Right Stick
						printf("Right X = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX));
						printf("Y = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY));
						//trigger buttons
						printf("Left Trigger = %i ", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT));
						printf("Right Trigger = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT));
	}
}

//==============================================================================

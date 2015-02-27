//==============================================================================
#include "HardLight.h"

//==============================================================================
int HardLight::OnExecute()
{
	if(!OnInit()) return EXIT_FAILURE;
	if(!BuildScene()) return EXIT_FAILURE;
	if(!CreateVehicle(bike, PxVec3(0,30,500))) return EXIT_FAILURE;
	//if(!CreateVehicle(PxVec3(0,50,600))) return EXIT_FAILURE;

    SDL_Event Event;

    while(running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();
	
	return EXIT_SUCCESS;
}

//==============================================================================

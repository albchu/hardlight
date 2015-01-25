//==============================================================================
#include "HardLight.h"

//==============================================================================
int HardLight::OnExecute()
{
	if(!OnInit()) return EXIT_FAILURE;
	if(!BuildScene()) exit(EXIT_FAILURE);

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

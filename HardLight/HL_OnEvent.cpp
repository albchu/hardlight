//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnEvent(SDL_Event* Event)
{
    if(Event->type == SDL_QUIT) {
        running = false;
    }
}

//==============================================================================

//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnLoop()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msPhysics < 1000 / 60) return;
	Uint32 elapsed = msCurrent - msPhysics;
	if (elapsed > msMax) elapsed = msMax;
	gScene->simulate(elapsed / 1000.0f);
	msPhysics = msCurrent;

	while(!gScene->fetchResults() )
	{
		
	}
}

//==============================================================================

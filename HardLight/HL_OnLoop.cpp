//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnLoop()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msPhysics < 1000 / 60) return;

	float elapsed = msCurrent - msPhysics;
	elapsed /= 1000.0;
	gScene->simulate(elapsed);
	msPhysics = msCurrent;

	while(!gScene->fetchResults() )
	{
		
	}
}

//==============================================================================

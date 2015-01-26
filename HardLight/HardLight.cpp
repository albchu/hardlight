//==============================================================================
#include "HardLight.h"

//==============================================================================
HardLight::HardLight()
{
    running = true;

	window_width = 1024;
	window_height = 768;
    window = NULL;
	glcontext = NULL;
	
	gScene = NULL;
	gPhysics = NULL;
	gFoundation = NULL;
	gDefaultFilterShader = PxDefaultSimulationFilterShader;
	
	globalGravity = -9.8f;
	msPhysics = SDL_GetTicks();
	msGraphics = msPhysics;

	grid_size = 10;
	nbObjects = 2;

	gCameraPos = PxVec3(5.0f, 7.0f, 20.0f);
	gCameraForward = PxVec3(-0.3f, 0.0f, -1.0f);

}

//==============================================================================

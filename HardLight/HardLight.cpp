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
	msMax = 100;

	grid_size = 10;
	nbObjects = 150;

	gCameraPos = PxVec3(5.0f, 7.0f, 20.0f);
	gCameraForward = PxVec3(-0.3f, 0.0f, -1.0f);
	lightAmbientColour[0] = lightAmbientColour[1] = lightAmbientColour[2] = 0.4f;
	lightAmbientColour[3] = 1.0f;
	lightDiffuseColour[0] = lightDiffuseColour[1] = lightDiffuseColour[2] = 0.8f;
	lightDiffuseColour[3] = 1.0f;
	lightSpecularColour[0] = lightSpecularColour[1] = lightSpecularColour[2] = 0.8f;
	lightSpecularColour[3] = 1.0f;

}

//==============================================================================

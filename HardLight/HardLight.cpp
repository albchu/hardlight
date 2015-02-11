//==============================================================================
#include "HardLight.h"

//==============================================================================
HardLight::HardLight()
{
	config = new INIReader("config.ini");
	if (config->ParseError() < 0) {
		fprintf(stderr, "Can't load 'config.ini'\n");
		exit(EXIT_FAILURE);
    }
	running = true;

	window_width = config->GetInteger("window", "width", 800);
	window_height = config->GetInteger("window", "height", 600);
	window = NULL;
	glcontext = NULL;

	gScene = NULL;
	gPhysics = NULL;
	gFoundation = NULL;
	gDefaultFilterShader = PxDefaultSimulationFilterShader;

	msPhysics = SDL_GetTicks();
	msGraphics = msPhysics;
	msMax = config->GetInteger("physics", "msMax", 100);

	nbObjects = config->GetInteger("scene", "nbObjects", 150);
	size = (float)config->GetReal("scene", "size", 10);

	gCameraPos = PxVec3(5.0f, 7.0f, 20.0f);
	gCameraForward = PxVec3(-0.3f, 0.0f, -1.0f);
	speed = (float)config->GetReal("controls", "speed", 1.0);
	fast = (float)config->GetReal("controls", "fast", 2.0);
	left = right = forward = back = 0;
	lightAmbientColour[0] = lightAmbientColour[1] = lightAmbientColour[2] = 0.4f;
	lightAmbientColour[3] = 1.0f;
	lightDiffuseColour[0] = lightDiffuseColour[1] = lightDiffuseColour[2] = 0.8f;
	lightDiffuseColour[3] = 1.0f;
	lightSpecularColour[0] = lightSpecularColour[1] = lightSpecularColour[2] = 0.8f;
	lightSpecularColour[3] = 1.0f;
}
//==============================================================================
HardLight::~HardLight()
{
	delete config;
}

//==============================================================================

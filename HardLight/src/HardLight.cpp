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
	scene = GAME;

	window_width = config->GetInteger("window", "width", 800);
	window_height = config->GetInteger("window", "height", 600);
	window = NULL;
	glcontext = NULL;

	msPhysics = SDL_GetTicks();
	msGraphics = msPhysics;
	msMax = config->GetInteger("physics", "msMax", 100);

	speed = (float)config->GetReal("controls", "speed", 1.0);
	fast = (float)config->GetReal("controls", "fast", 2.0);
	left = right = forward = back = 0;

	srand ((unsigned int)time(NULL));
	//bike->setInAir(true);
}
//==============================================================================
HardLight::~HardLight()
{
	delete config;
}

//==============================================================================

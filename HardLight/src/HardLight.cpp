//==============================================================================
#include "HardLight.h"

//==============================================================================
HardLight::HardLight()
{
	srand ((unsigned int)time(NULL));	// Seed for random value generator

	config = new INIReader("config.ini");
	if (config->ParseError() < 0) {
		fprintf(stderr, "Can't load 'config.ini'\n");
		exit(EXIT_FAILURE);
	}
	running = true;

	window_width = config->GetInteger("window", "width", 800);
	window_height = config->GetInteger("window", "height", 600);
	size = (float)config->GetReal("scene", "size", 300.0);
	gravity = (float)config->GetReal("scene", "gravity", 9.81);
	dampening = (float)config->GetReal("bike", "dampening", 0.0);
	window = NULL;
	glcontext = NULL;

	msPhysics = SDL_GetTicks();
	msGraphics = msPhysics;
	msMax = config->GetInteger("physics", "msMax", 100);

	speed = (float)config->GetReal("controls", "speed", 1.0);
	classic = config->GetBoolean("camera", "classic", false);

	switch (config->GetInteger("scene", "map", MapTypes::SPHERE))
	{
	case 0:
		map_type = MapTypes::PLANE;
		break;
	case 1:
		map_type = MapTypes::SPHERE;
		break;
	default:
		map_type = MapTypes::SPHERE;
		break;
	}

	//bike->setInAir(true);
}

//==============================================================================
HardLight::~HardLight()
{
	delete config;
}

//==============================================================================

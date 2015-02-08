//==============================================================================
#include "HardLight.h"

//==============================================================================
bool HardLight::OnInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    	    8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  	    8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   	    8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  	    8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  	    16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,		    32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,	    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,	    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,	8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	if((window = SDL_CreateWindow("Hard Light", 8, 31, window_width, window_height, SDL_WINDOW_OPENGL)) == NULL)
	{
		return false;
	}

	if (config->GetBoolean("window", "fullscreen", false) && SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
	{
		return false;
	}
<<<<<<< HEAD

	if ((glcontext = SDL_GL_CreateContext(window)) == NULL)
	{
		return false;
	}
=======
>>>>>>> 00ac14d3669a7689e009be3782b0a2cd8866f27f
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				controller = SDL_GameControllerOpen(i);
				if (controller) {
					break;
				} else {
				return false;
		}
	}
	}
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if(!gFoundation)
	{
		return false;
	}

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());
	if(gPhysics == NULL)
	{
		return false;
	}

	if(!PxInitExtensions(*gPhysics))
	{
		return false;
	}

	if(!PxInitVehicleSDK(*gPhysics))
	{
		return false;
	}
	PxVehicleSetBasisVectors(PxVec3(0,1,0), PxVec3(0,0,1));
	PxVehicleSetUpdateMode(PxVehicleUpdateMode::eACCELERATION);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(
		(float)config->GetReal("gravity", "x", 0.0),
		(float)config->GetReal("gravity", "y", 0.0),
		(float)config->GetReal("gravity", "z", 0.0)
		);

	if(!sceneDesc.cpuDispatcher)
	{
		physx::PxDefaultCpuDispatcher* mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
		if(!mCpuDispatcher)
		{
			return false;
		}
		sceneDesc.cpuDispatcher = mCpuDispatcher;
	}
	if(!sceneDesc.filterShader)
	{
		sceneDesc.filterShader = gDefaultFilterShader;
	}

	gScene = gPhysics->createScene(sceneDesc);
	if(!gScene)
	{
		return false;
	}

	return true;
}

//==============================================================================

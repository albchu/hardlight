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

	if ((glcontext = SDL_GL_CreateContext(window)) == NULL)
	{
		return false;
	}
	cout << "Number of controllers detected: "<<SDL_NumJoysticks()<<endl;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));

		}
	}
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocator, gDefaultErrorCallback);
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
	PxVehicleSetUpdateMode(PxVehicleUpdateMode::eVELOCITY_CHANGE);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(
		(float)config->GetReal("gravity", "x", 0.0),
		(float)config->GetReal("gravity", "y", 0.0),
		(float)config->GetReal("gravity", "z", 0.0)
		);

	if(!sceneDesc.cpuDispatcher)
	{
		PxDefaultCpuDispatcher* mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
		if(!mCpuDispatcher)
		{
			return false;
		}
		sceneDesc.cpuDispatcher = mCpuDispatcher;
	}

	if(!sceneDesc.filterShader)
	{
		sceneDesc.filterShader = VehicleFilterShader;
	}

	gScene = gPhysics->createScene(sceneDesc);
	if(!gScene)
	{
		return false;
	}

	gCooking = 	PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));

	// GLEW Library Initialization
	glewExperimental=true; // Needed in Core Profile
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	projection_matrix = perspective(
		(float)config->GetReal("camera", "fov", 60.0)/180.0f*PxPi,
		(float)window_width/(float)window_height,
		0.1f, 3200.0f);

	cam_translate = vec3(
		(float)config->GetReal("camera", "x", 0.0),
		(float)config->GetReal("camera", "y", 5.0),
		(float)config->GetReal("camera", "z", -10.0));
	cam_rotate = 0.0f;

	// Print OpenGL information
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}

//==============================================================================
//==============================================================================
#include "HardLight.h"

//==============================================================================
//int getNbCores()
//{
//	return 4;
//}
//
//PxFilterFlags gFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
//							PxFilterObjectAttributes attributes1, PxFilterData filterData1,
//							PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
//{
//	// let triggers through
//	if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
//	{
//		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
//		return PxFilterFlag::eDEFAULT;
//	}
//
//	if( (0 == (filterData0.word0 & filterData1.word1)) && (0 == (filterData1.word0 & filterData0.word1)) )
//		return PxFilterFlag::eSUPPRESS;
//
//	pairFlags = PxPairFlag::eCONTACT_DEFAULT;
//
//	if (((filterData0.word0 & COLLISION_FLAG_CHASSIS) && (filterData1.word0 & COLLISION_FLAG_OBSTACLE))
//		|| ((filterData0.word0 & COLLISION_FLAG_CHASSIS) && (filterData1.word0 & COLLISION_FLAG_CHASSIS))
//		|| ((filterData0.word0 & COLLISION_FLAG_OBSTACLE) && (filterData1.word0 & COLLISION_FLAG_CHASSIS))
//		)
//	{
//		pairFlags = pairFlags | PxPairFlag::eNOTIFY_TOUCH_FOUND;
//	}
//
//	return PxFilterFlag::eDEFAULT;
//}


// initializes openGL
// separates initialization by scene type
void HardLight::initOpenGL(Scene scene) {
	if(scene == GAME) {
		// Dark blue background
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);


		projection_matrix = perspective(
			(float)config->GetReal("camera", "fov", 60.0)/180.0f*PxPi,
			(float)window_width/(float)window_height,
			0.1f, 10000.0f);

		cam_translate = vec3(
			(float)config->GetReal("camera", "x", 0.0),
			(float)config->GetReal("camera", "y", 5.0),
			(float)config->GetReal("camera", "z", -10.0));
		cam_rotate = 0.0f;
	}
	else {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		projection_matrix = ortho(0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1.0f);
	}
}

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

	//Initialize physx agent to govern all shared physx objects
	pxAgent = new Physx_Agent(config, this);

	// GLEW Library Initialization
	glewExperimental=true; // Needed in Core Profile
	if (glewInit() != GLEW_OK)
		return false;

	initOpenGL(scene);

	// Print OpenGL information
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	if (!sfxMix.InitializeMixer(config))
		return false;

	bikes = new Bikes(&world);

	// Init AI system to govern bots
	overMind = new AI(bikes);



	return true;
}

//==============================================================================
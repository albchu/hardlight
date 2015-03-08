//==============================================================================
#include "HardLight.h"

//==============================================================================

//==============================================================================
bool HardLight::OnInit()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cerr << "Could not initialize SDL" << endl;

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 4);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

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

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	if((window = SDL_CreateWindow("Hard Light", 8, 31, window_width, window_height, SDL_WINDOW_OPENGL)) == NULL)
		cerr << "Could not create SDL window" << endl;

	if (config->GetBoolean("window", "fullscreen", false) && SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		cerr << "Could not make SDL window fullscreen" << endl;

	if ((glcontext = SDL_GL_CreateContext(window)) == NULL)
		cerr << "Could not make SDL OpenGl context" << endl;

	cout << "Number of controllers detected: "<<SDL_NumJoysticks()<<endl;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));
		}
	}

	//Initialize physx agent to govern all shared physx objects
	pxAgent = new PhysxAgent(config, this);

	// GLEW Library Initialization
	glewExperimental=true; // Needed in Core Profile
	if (glewInit() != GLEW_OK)
		cerr << "Could not make initialize glew" << endl;

	scene = GAME;
	gui = GUI(window);
	gui.loadMenu("MainMenu.txt", pxAgent->get_physics());

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

	// Print OpenGL information
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	if (!sfxMix.InitializeMixer(config))
		cerr << "Could not initialize sound mixer" << endl;

	bikes = new Bikes(&world, config);

	// Init AI system to govern bots
	overMind = new AI(bikes);
	
	// Init Powerup object for testing powerup functionality temporarily
	powerup = new Powerup(NULL, bikes, config);	

	return true;
}

//==============================================================================
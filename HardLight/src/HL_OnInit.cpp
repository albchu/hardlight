//==============================================================================
#include "HardLight.h"

//==============================================================================

bool HardLight::OnInit()
{
	// Enforce that we cannot support more than 4 players. It either fails here or bombs out our program in a spot thats hard to debug
	if(config->GetInteger("game", "numPlayers", 1) > 4)
	{
		cerr << "Please enter a number between 0-4 in the config.ini for numPlayers" << endl;
		return false;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cerr << "Could not initialize SDL" << endl;

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	if(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1) < 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
	}
	if(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16) < 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
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

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  4);

	if((window = SDL_CreateWindow("Hard Light", 8, 31, window_width, window_height, SDL_WINDOW_OPENGL)) == NULL)
		cerr << "Could not create SDL window" << endl;

	if (config->GetBoolean("window", "fullscreen", false) && SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		cerr << "Could not make SDL window fullscreen" << endl;

	SDL_GetWindowSize(window, &window_width, &window_height);

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

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	// Print OpenGL information
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	if (!sfxMix.InitializeMixer(config))
		cerr << "Could not initialize sound mixer" << endl;

	bike_manager = new BikeManager(&world, config, pxAgent);

	// Init Powerup object for testing powerup functionality temporarily
	//powerup = new Powerup(NULL, bike_manager, config);

	// Initialize viewport info
	int cams = glm::max(config->GetInteger("game", "numCameras", 1), config->GetInteger("game", "numPlayers", 1));
	
	viewports = Viewports::generate_viewports(cams, window_width, window_height);

	// Initialize keyboard player control info
	keyMappings = KeyMappings::generate_keyMappings();

	// Init AI system to govern bots
	overMind = new AI(bike_manager, &sfxMix);
	
	sfxMix.PlayMusic("musicOverworld");

	// Init powerup manager
	powerup_manager = new PowerupManager(&world, config, pxAgent, &sfxMix);

	// Create a pixmap font from a TrueType file.
	font = new FTGLPixmapFont ("../data/Fonts/Roboto-Bold.ttf");
	//
	// If something went wrong, bail out.
	if(font->Error())
		return -1;


	return true;
}

//==============================================================================
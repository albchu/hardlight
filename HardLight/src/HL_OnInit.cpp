//==============================================================================
#include "HardLight.h"

//==============================================================================

bool HardLight::OnInit()
{
	cams = glm::max(config->GetInteger("game", "numCameras", 1), (long)numPlayers);
	numPlayers = config->GetInteger("game", "numPlayers", 1);	// Subtract 1 because of menu input and the fact that base starts at 1. Trust Albert on this
	numBots = config->GetInteger("game", "numBots", 0);	
	numInstantPowerups = config->GetInteger("powerup", "maxInstants", 1);
	numHoldPowerups = config->GetInteger("powerup", "maxHolds", 1);

	// Enforce that we cannot support more than 4 players. It either fails here or bombs out our program in a spot thats hard to debug
	if(numPlayers > 4)
	{
		cerr << "Please enter a number between 0-4 in the config.ini for numPlayers" << endl;
		return false;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cerr << "Could not initialize SDL" << endl;

	//Set texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
		return false;
	}

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


	//Create vsynced renderer for window
	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( gRenderer == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	isFullscreen = config->GetBoolean("window", "fullscreen", false);	// May god have mercy on the man's soul that turns this on before final submission

	if(SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) < 0)
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

	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
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

	// Initialize keyboard player control info
	keyMappings = KeyMappings::generate_keyMappings();

	// Init AI system to govern bots
	overMind = new AI(bike_manager, &sfxMix, config);

	sfxMix.PlayMusic("musicOverworld");

	// Init powerup manager
	powerup_manager = new PowerupManager(&world, config, pxAgent, &sfxMix);

	// Create a pixmap font from a TrueType file.
	font = new FTBitmapFont ("../data/Fonts/Roboto-Bold.ttf");
	//
	// If something went wrong, bail out.
	if(font->Error())
		return false;
	display_message = "HelloWorld!!";

	// Initialize menu manager
	menuManager = new MenuManager(gRenderer, 0,0, window_width, window_height);
	menu_active = true;
	game_launched = false;
	scene_built = false;

	// Variables to track when to calculate different stages of onLoop
	deathCalc = new LoopTimer(5);
	powerupCalc = new LoopTimer(5);
	winCalc = new LoopTimer(50);

	return true;
}

//==============================================================================
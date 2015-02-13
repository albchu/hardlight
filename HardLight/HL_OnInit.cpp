//==============================================================================
#include "HardLight.h"

//==============================================================================

// searches directory for .objs and fills list of parsed objs
void HardLight::loadAllOBJs(const char* directory) {

	char searchPath[200];

	sprintf(searchPath, "%s*.obj", directory);
	WIN32_FIND_DATA fd;
	HANDLE handle = ::FindFirstFile((LPCWSTR)searchPath, &fd);
	if(handle != INVALID_HANDLE_VALUE) { 
        do { 

            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {

				std::string dirString = std::string(directory);
				std::string filename = std::string((char*)fd.cFileName);
				parsedOBJs.push_back(Parser((dirString + filename).c_str()));
            }
        }while(::FindNextFile(handle, &fd)); 
        ::FindClose(handle); 
    } 
}

bool HardLight::OnInit()
{
	loadAllOBJs("../data/");

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
	if( glewInit() != GLEW_OK )
	{
		return false;
	}
	glEnable( GL_DEPTH_TEST );

	//ALBERTS MESS, DONT TOUCH PLEASE
	// Camera Initialization
	//GLuint render_prog = CreateShaderProgram("basic_vs.glsl", "basic_fs.glsl");
	//glUseProgram(render_prog);
	//view_matrix = mat4(1.0f);
	projection_matrix = perspective(45.0f, (float)window_width/(float)window_height, 0.1f, 1000.0f);

	view_matrix = translate(view_matrix, vec3(0,-10,-10));
	//render_projection_matrix_loc = glGetUniformLocation(GL_PROJECTION, "projection_matrix");
	//glUniformMatrix4fv(render_projection_matrix_loc,		// ID
	//	1,
	//	GL_FALSE,
	//	glm::value_ptr(projection_matrix)	// pointer to data in Mat4f
	//	);

	//old way. dont forget to comment out some of camera code in ONRENDER
	//gCameraPos += PxVec3((right-left)*speed, 0.0f, (back-forward)*speed);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(60.0f, window_width/(float)window_height, 1.0f, 10000.0f);
	//gluLookAt(gCameraPos.x, gCameraPos.y, gCameraPos.z,
	//	gCameraPos.x + gCameraForward.x, gCameraPos.y + gCameraForward.y, gCameraPos.z + gCameraForward.z,
	//	0.0f, 1.0f, 0.0f);
	
	// Print OpenGL information
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return true;
}

//==============================================================================
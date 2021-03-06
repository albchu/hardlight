#ifndef _HARDLIGHT_H_
#define _HARDLIGHT_H_

#include <stdio.h>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include <sstream>
#include "../inih\cpp\INIReader.h"

#include <GL\glew.h>

#include <SDL_opengl.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL\GL.h>

#include <PxPhysicsAPI.h>

#include <FTGL/ftgl.h>

#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "objParser.h"
#include "World.h"
#include "AI/AI.h"
#include "Controls/Controller.h"
#include "Controls/Player_Controller.h"
#include "Controls/Bot_Controller.h"
#include "Entity.h"
#include "Vehicle/Chassis.h"
#include "Vehicle/BikeManager.h"
#include "SkyBox.h"
#include "Wall.h"
#include "Common.h"
#include "Vehicle/TailSegment.h"
#include "Vehicle/TailWall.h"
#include "MeshMap.h"
#include "Rendering/TextureMap.h"
#include "GUI.h"
#include "SceneTypes.h"
#include "SoundMixer.h"
#include "Vehicle/CreateVehicle.h"
#include "Powerup/Powerup.h"
#include "Rendering/Viewports.h"
#include "KeyMappings.h"
#include "MapTypes.h"
#include "Powerup/PowerupManager.h"
#include "ParticleFactory.h"
#include "ParticleSystem.h"
#include "Rendering/LTexture.h"
#include "Menu/MenuManager.h"
#include "LoopTimer.h"
#include "Scoreboard.h"


using namespace physx;
using namespace glm;

#pragma comment(lib, "ftgl_static_D.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PxTaskDEBUG.lib")
#pragma comment(lib, "PhysX3VehicleDEBUG.lib")
#pragma comment(lib, "PhysX3CookingDEBUG_x86.lib")
#pragma comment(lib, "PhysXProfileSDKDEBUG.lib")
#pragma comment(lib, "PhysXVisualDebuggerSDKDEBUG.lib")

//==============================================================================
class HardLight : public PxSimulationEventCallback
{
private:
	vector<Viewports::Viewport> viewports;
	vector<KeyMapping> keyMappings;		// Holds an array of keyboard commands for a particular bike
	INIReader* config;
	bool running;
	Scene scene;
	GUI gui;

	int window_width;
	int window_height;
	SDL_Window* window;
	SDL_GLContext glcontext;

	//The window renderer
	SDL_Renderer* gRenderer;

	vector<SDL_GameController*> controllers;

	PhysxAgent* pxAgent;

	// Implements PxSimulationEventCallback
	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	virtual void onTrigger(PxTriggerPair*, PxU32);
	virtual void onConstraintBreak(PxConstraintInfo*, PxU32) {}
	virtual void onWake(PxActor**, PxU32) {}
	virtual void onSleep(PxActor**, PxU32) {}

	// scene specific functions
	void initOpenGL(Scene);

	int maxParticles;
	float particleSpeed;
	double explosionLifeSpan;
	PxParticleSystem* particleSystem;
	ParticleData particleData;
	PxParticleCreationData particleCreationData;

	Uint32 msGraphics;
	Uint32 msPhysics;
	Uint32 msMax;

	float speed;

	World world;
	float size;
	float gravity;
	float dampening;
	bool classic;
	MapTypes map_type;

	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs;

	Menu* menu;		// Currently this is a hardcoded value appended to the first bike at all times. we dont like this. Albert is to blame. 
	SkyBox* skybox;
	vec3 oldPos;
	vector<TailSegment*> playerTail;
	BikeManager* bike_manager;		// Holds arrays of all bike_manager on the scene
	vector<Bike*> bikesToKill;
	vector<tuple<Bike*,PxRigidActor*>> bikePowerupPairs;		//Used to map a bike to a powerup that it collides with
	AI* overMind;

	SoundMixer sfxMix;	// Create a Mixer that holds all sound files
	Scoreboard scoreboard;

	FTBitmapFont * font;	// THIS CODE IS BAD AND SHOULDNT BE HARD INSTANTIATED LIKE THIS
	const char * display_message;
	PowerupManager* powerup_manager;
	const char* powerUpMessage;

	bool menu_active; // Determines when we switch renderers to the menu in the game
	bool game_launched;

	MenuManager* menuManager;
	Menu* pauseMenu;
	MenuOption* loadingMessage;
	MenuOption* fullscreenOption;
	MenuOption* classicOption;
	bool isFullscreen;
	bool scene_built;
	int resolutionIndex;
	bool settings_update;	// Triggered when some settings have been updated
	bool halt_trigger;		// Used if the player wants to go back to main menu
	bool restart_trigger;
	bool continue_trigger;	// If the game is paused, this will resume it
	int cams;
	int numPlayersMenu;		// Tracks the number of players in menu selection. Needs to be separate due to constant iteration in buildscene issue
	int numPlayers;
	int numBots;
	int numInstantPowerups;
	int numHoldPowerups;
	Uint32 timer;

	// Variables to track when to calculate different stages of onLoop
	LoopTimer* deathCalc;
	LoopTimer* powerupCalc;
	LoopTimer* winCalc;

public:
	HardLight();
	~HardLight();

	int OnExecute();

	bool OnInit();

	bool BuildScene();

	void OnEvent(SDL_Event* Event);

	void OnLoop();

	void OnRender();

	void OnCleanup();

	void reset();

	void toggle_pause();

	bool menu_init();

	void menu_update();

	void loading_update(const char * message);
};

//==============================================================================
#endif

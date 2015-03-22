#ifndef _HARDLIGHT_H_
#define _HARDLIGHT_H_

#include <stdio.h>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include "../inih\cpp\INIReader.h"

#include <GL\glew.h>

#include <SDL_opengl.h>
#include <SDL.h>
#include <GL\GL.h>

#include <PxPhysicsAPI.h>

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
#include "Menu.h"
#include "GUI.h"
#include "SceneTypes.h"
#include "SoundMixer.h"
#include "Vehicle/CreateVehicle.h"
#include "Powerup.h"
#include "Pickup.h"
#include "Menu.h"
#include "Rendering/Viewports.h"
#include "KeyMappings.h"
#include "PowerupManager.h"

using namespace physx;
using namespace glm;

#pragma comment(lib, "glew32.lib")
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
	bool spawnBikes();

	Uint32 msGraphics;
	Uint32 msPhysics;
	Uint32 msMax;

	float speed;
	float fast;
	float forward;
	float back;
	float left;
	float right;

	World world;
	float size;

	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs;

	Menu* menu;		// Currently this is a hardcoded value appended to the first bike at all times. we dont like this. Albert is to blame. 
	SkyBox* skybox;
	vec3 oldPos;
	vector<TailSegment*> playerTail;
	BikeManager* bike_manager;		// Holds arrays of all bike_manager on the scene
	vector<Bike*> bikesToKill;
	//vector<Chassis*> hit_pickup;
	//vector<PxRigidActor*> pickup_hit;
	vector<tuple<PxRigidActor*,PxRigidActor*>> bikePowerupPairs;		//Used to map a bike to a powerup that it collides with
	AI* overMind;

	SoundMixer sfxMix;	// Create a Mixer that holds all sound files
	
	PowerupManager* powerup_manager;

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
};

//==============================================================================
#endif

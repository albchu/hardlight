#ifndef _HARDLIGHT_H_
#define _HARDLIGHT_H_

#include <stdio.h>
#include <vector>
#include <string>
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
#include "Vehicle/Bike.h"
#include "Vehicle/Bikes.h"
#include "SkyBox.h"
#include "Wall.h"
#include "Common.h"
#include "Vehicle/TailSegment.h"
#include "Vehicle/TailWall.h"
#include "MeshMap.h"
#include "Rendering/TextureMap.h"

#include "SoundMixer.h"
#include "Vehicle/CreateVehicle.h"


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

enum Scene {
	MENU,
	GAME
};

//==============================================================================
class HardLight : public PxSimulationEventCallback
{
private:
	INIReader* config;
	bool running;
	Scene scene;

	int window_width;
	int window_height;
	SDL_Window* window;
	SDL_GLContext glcontext;
	
	vector<SDL_GameController*> controllers;

	Physx_Agent* pxAgent;

	// Implements PxSimulationEventCallback
	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	virtual void onTrigger(PxTriggerPair*, PxU32) {}
	virtual void onConstraintBreak(PxConstraintInfo*, PxU32) {}
	virtual void onWake(PxActor**, PxU32) {}
	virtual void onSleep(PxActor**, PxU32) {}

	// scene specific functions
	void initOpenGL(Scene);

	Uint32 msGraphics;
	Uint32 msPhysics;
	Uint32 msMax;

	float speed;
	float fast;
	float forward;
	float back;
	float left;
	float right;

	mat4 projection_matrix;
	vec3 cam_translate;
	float cam_rotate;

	World world;
	float size;

	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs;

	SkyBox* skybox;
	vec3 oldPos;
	vector<TailSegment*> playerTail;
	Bikes* bikes;		// Holds arrays of all bikes on the scene
	vector<Bike*> bikesToKill;
	AI* overMind;

	SoundMixer sfxMix;	// Create a Mixer that holds all sound files

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
};

//==============================================================================
#endif

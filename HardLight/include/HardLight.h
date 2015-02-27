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
#include "Entity.h"
#include "Bike.h"
#include "Bikes.h"
#include "SkyBox.h"
#include "TailWall.h"


using namespace physx;
using namespace glm;

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PxTaskDEBUG.lib")
#pragma comment(lib, "PhysX3VehicleDEBUG.lib")
#pragma comment(lib, "PhysX3CookingDEBUG_x86.lib")

//==============================================================================
class HardLight
{
private:
	INIReader* config;
	bool running;

	int window_width;
	int window_height;
	SDL_Window* window;
	SDL_GLContext glcontext;
	SDL_GameController* controller;
	vector<SDL_GameController*> controllers;

	PxScene* gScene;
	PxFoundation* gFoundation;
	PxPhysics* gPhysics;
	PxCooking* gCooking;
	PxDefaultErrorCallback gDefaultErrorCallback;
	PxDefaultAllocator gDefaultAllocator;
	PxSimulationFilterShader gDefaultFilterShader;

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
	
	//vehicles
	//VehicleSceneQueryData* gVehicleSceneQueryData;
	//PxBatchQuery* gBatchQuery;

	PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs;
	PxRigidStatic* gGroundPlane;
	//PxVehicleDrive4W* gVehicle4W;
	//PxRigidActor* vehicle;
	//bool gIsVehicleInAir;
	//PxVehicleDrive4WRawInputData gVehicleInputData;
	//tail
	//SkyBox skybox;
	TailWall tail;

	Bike* bike;
	Bikes bikes;		// Holds arrays of all bikes on the scene

public:
	HardLight();
	~HardLight();

	int OnExecute();

	bool OnInit();

	bool BuildScene();

	bool CreateVehicle(Bike* &bike, PxVec3 init_position);

	void OnEvent(SDL_Event* Event);

	void OnLoop();

	void OnRender();

	void OnCleanup();
};

//==============================================================================
#endif
#ifndef _HARDLIGHT_H_
#define _HARDLIGHT_H_

#include <stdio.h>
#include <vector>

#include <SDL_opengl.h>
#include <SDL.h>
#include <gl\GLU.h>

#include <PxPhysicsAPI.h>

using namespace physx;

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PxTaskDEBUG.lib")

//==============================================================================
class HardLight
{
private:
	bool running;

	int window_width;
	int window_height;
	SDL_Window* window;
	SDL_GLContext glcontext;
	SDL_GameController* controller;

	PxScene* gScene;
	PxFoundation* gFoundation;
	PxPhysics* gPhysics;
	PxDefaultErrorCallback gDefaultErrorCallback;
	PxDefaultAllocator gDefaultAllocatorCallback;
	PxSimulationFilterShader gDefaultFilterShader;

	float globalGravity;
	Uint32 msGraphics;
	Uint32 msPhysics;
	Uint32 msMax;

	int grid_size;
	int nbObjects;

	PxVec3 gCameraPos;
	PxVec3 gCameraForward;
	GLfloat lightAmbientColour[4];
	GLfloat lightDiffuseColour[4];
	GLfloat lightSpecularColour[4];

	void DrawRigidActor(PxRigidActor* actor);

public:
	HardLight();

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

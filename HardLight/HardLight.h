#ifndef _HARDLIGHT_H_
#define _HARDLIGHT_H_

#include <stdio.h>
#include <vector>

#include <SDL_opengl.h>
#include <SDL.h>
#include <gl\GLU.h>

#include <PxPhysicsAPI.h>
#include <extensions\PxExtensionsAPI.h>
#include <extensions\PxDefaultErrorCallback.h>
#include <extensions\PxDefaultAllocator.h>
#include <extensions\PxDefaultSimulationFilterShader.h>
#include <extensions\PxDefaultCpuDispatcher.h>
#include <extensions\PxShapeExt.h>
#include <extensions\PxSimpleFactory.h>
#include <foundation\PxFoundation.h>
#include <foundation\PxMat33.h>

using namespace physx;

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PxTaskDEBUG.lib")

#pragma warning(disable : 4099)

//==============================================================================
class HardLight
{
private:
	bool running;

	int window_width;
	int window_height;
	SDL_Window* window;
	SDL_GLContext glcontext;

	PxScene* gScene;
	PxFoundation* gFoundation;
	PxPhysics* gPhysics;
	PxDefaultErrorCallback gDefaultErrorCallback;
	PxDefaultAllocator gDefaultAllocatorCallback;
	PxSimulationFilterShader gDefaultFilterShader;

	float globalGravity;
	Uint32 msGraphics;
	Uint32 msPhysics;

	int grid_size;
	int nbObjects;

	PxVec3 gCameraPos;
	PxVec3 gCameraForward;

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

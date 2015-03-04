#ifndef _PHYSX_AGENT_H_
#define _PHYSX_AGENT_H_

#include <glm/glm.hpp>		// Used for vec3
#include <PxPhysicsAPI.h>
#include <iostream>
#include "../inih\cpp\INIReader.h"

#include "../SnippetVehicleCommon/SnippetVehicleRaycast.h"
#include "../SnippetVehicleCommon/SnippetVehicleFilterShader.h"
#include "../SnippetVehicleCommon/SnippetVehicleTireFriction.h"
#include "../SnippetVehicleCommon/SnippetVehicleCreate.h"

using namespace std;
using namespace glm;
using namespace physx;

// This class should be the single point of access for all our physx objects and also general useful functions
class Physx_Agent
{
public:
	Physx_Agent(INIReader* new_config, PxDefaultAllocator& gAllocator, PxDefaultErrorCallback& gErrorCallback);
	static vec3 toVec3(PxVec3);
	PxPhysics* get_physics();
	PxScene* get_scene();
	PxFoundation* get_foundation();
	PxDefaultCpuDispatcher* get_dispatcher();
	void cleanup();

private:
	PxScene* gScene;
	PxPhysics* gPhysics;
	INIReader* config;
	PxFoundation* gFoundation;
	PxDefaultCpuDispatcher* gDispatcher;
};
#endif
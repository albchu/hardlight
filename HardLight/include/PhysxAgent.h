#ifndef _PHYSX_AGENT_H_
#define _PHYSX_AGENT_H_

#include <glm/glm.hpp>		// Used for vec3
#include <PxPhysicsAPI.h>
#include <iostream>
#include <vector>
#include "../inih\cpp\INIReader.h"
#include "MeshData.h"
#include "EntityTypes.h"

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
	Physx_Agent(INIReader* new_config, PxSimulationEventCallback* pxSimulationEventCallback);
	static vec3 toVec3(PxVec3);
	PxPhysics* get_physics();
	PxScene* get_scene();
	PxFoundation* get_foundation();
	PxDefaultCpuDispatcher* get_dispatcher();
	void cleanup();
	int getNbCores();
	static PxFilterFlags gFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);
	PxDefaultAllocator get_allocator();
	PxDefaultErrorCallback get_error_callback();
	PxRigidActor* create_static_mesh(MeshData*, PxTransform, EntityTypes);

private:
	PxScene* gScene;
	PxPhysics* gPhysics;
	INIReader* config;
	PxFoundation* gFoundation;
	PxDefaultCpuDispatcher* gDispatcher;
	PxDefaultAllocator gAllocator;
	PxDefaultErrorCallback gErrorCallback;
	PxVisualDebuggerConnection* gConnection;
	PxCooking* gCooking;
};
#endif
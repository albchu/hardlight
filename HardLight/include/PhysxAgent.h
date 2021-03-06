#ifndef _PHYSXAGENT_H_
#define _PHYSXAGENT_H_

#include <glm/glm.hpp>		// Used for vec3
#include <PxPhysicsAPI.h>
#include <iostream>
#include <vector>
#include "../inih\cpp\INIReader.h"
#include "MeshData.h"
#include "MeshMap.h"
#include "EntityTypes.h"

#include "../SnippetVehicleCommon/SnippetVehicleRaycast.h"
#include "../SnippetVehicleCommon/SnippetVehicleFilterShader.h"
#include "../SnippetVehicleCommon/SnippetVehicleTireFriction.h"
#include "../SnippetVehicleCommon/SnippetVehicleCreate.h"

using namespace std;
using namespace glm;
using namespace physx;

// This class should be the single point of access for all our physx objects and also general useful functions
class PhysxAgent
{
public:
	PhysxAgent(INIReader* new_config, PxSimulationEventCallback* pxSimulationEventCallback);
	static vec3 toVec3(PxVec3);
	static PxU32 collides_with(EntityTypes type);
	static PxU32 driveable(EntityTypes type);
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
	PxCooking* get_cooking();
	PxConvexMesh* create_convex_mesh(vector<vec3> vertices);
	PxRigidActor* create_static_convex_mesh(MeshData*, PxTransform, EntityTypes);
	PxRigidStatic* create_tail(vec3 old_location, vec3 new_location, vec3 up, float width, float height);
	PxRigidStatic* create_pickup(vec3 location, vec3 up, vec3 scaleFactors);
	PxRigidStatic* create_ground(vec3 scaleFactors);
	PxRigidStatic* create_ground_sphere(float scale_factor);
	PxRigidStatic* create_ground_plane();
	PxRigidStatic* create_wall_plane(PxPlane plane);
	void create_ai_vision(vec3 scaleFactors, vec3 transform, PxRigidActor* actor, void* bike);

	static PxQuat PxLookAt(vec3 direction, vec3 up);
	static PxQuat PxLookAt(PxVec3 direction, PxVec3 up);

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
	
	PxConvexMesh* tail_mesh;
	PxMaterial* tail_material;
	PxConvexMesh* pickup_mesh;
	PxMaterial* pickup_material;
	PxConvexMesh* ground_mesh;
	PxMaterial* ground_material;
	PxConvexMesh* wall_mesh;
	PxMaterial* wall_material;
	PxMaterial* ai_material;
};
#endif
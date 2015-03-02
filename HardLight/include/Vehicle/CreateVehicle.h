#ifndef _CREATE_VEHICLE_H
#define _CREATE_VEHICLE_H

#include <PxPhysicsAPI.h>
#include <vehicle/PxVehicleUtil.h>
#include "../SnippetVehicleCommon/SnippetVehicleRaycast.h"
#include "../SnippetVehicleCommon/SnippetVehicleFilterShader.h"
#include "../SnippetVehicleCommon/SnippetVehicleTireFriction.h"
#include "../SnippetVehicleCommon/SnippetVehicleCreate.h"

#include "Bike.h"
#include "../inih\cpp\INIReader.h"

using namespace std;

class CreateVehicle
{

public:
	CreateVehicle(INIReader* new_config, PxScene* new_gScene, PxPhysics* new_gPhysics, PxDefaultAllocator new_gAllocator, PxFoundation* new_gFoundation);
	bool Create(Bike* &bike, PxVec3 init_position);

private:
	INIReader* config;
	PxScene* gScene;
	PxPhysics* gPhysics;
	PxDefaultAllocator gAllocator;
	PxCooking* gCooking;
	PxFoundation* gFoundation;
	// PxActor is handled by Entity parent class of Bike
};
#endif
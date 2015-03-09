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
#include "MeshMap.h"
#include "PhysxAgent.h"

using namespace std;

class CreateVehicle
{

public:
	CreateVehicle(INIReader* new_config, PhysxAgent* new_pxAgent);
	bool Create(Bike* &bike, PxVec3 init_position);

private:
	INIReader* config;
	PhysxAgent* pxAgent;
	// PxActor is handled by Entity parent class of Bike
};
#endif
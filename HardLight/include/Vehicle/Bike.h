#ifndef _BIKE_H
#define _BIKE_H

#include "Entity.h"
#include "TailWall.h"

#include <PxPhysicsAPI.h>
#include <vehicle/PxVehicleUtil.h>
#include "../SnippetVehicleCommon/SnippetVehicleRaycast.h"
#include "../SnippetVehicleCommon/SnippetVehicleFilterShader.h"
#include "../SnippetVehicleCommon/SnippetVehicleTireFriction.h"
#include "../SnippetVehicleCommon/SnippetVehicleCreate.h"

#include <glm\gtx\rotate_vector.hpp>
#include <glm/glm.hpp>		// Used for vec3
#include "glm/gtx/string_cast.hpp"		// Used for to_string

using namespace glm;
using namespace std;

class Bike : public Entity
{

public:
	Bike();//:Entity(actor, meshdata, texture){};
	Bike(PxRigidActor* actor, const char* texture);//:Entity(actor, meshdata, texture){};
	~Bike();
	virtual mat4 get_model_matrix();

	PxVehicleDrive4W* getVehicle4W();
	PxVehicleDrive4WRawInputData& getInputData();
	VehicleSceneQueryData* getVehicleSceneQueryData();
	PxBatchQuery* getBatchQuery();
	bool isInAir();
	bool invincible;

	void setVehicle4W(PxVehicleDrive4W*);
	void setInputData(PxVehicleDrive4WRawInputData);
	void setVehicleSceneQueryData(VehicleSceneQueryData*);
	void setBatchQuery(PxBatchQuery*);
	void setInAir(bool);

	TailWall* get_tail_wall();

private:
	PxVehicleDrive4W* vehicle4W;
	PxVehicleDrive4WRawInputData inputData;
	VehicleSceneQueryData* vehicleSceneQueryData;
	PxBatchQuery* batchQuery;
	bool inAir;
	TailWall* tail_wall;
	// PxActor is handled by Entity parent class of Bike
};
#endif
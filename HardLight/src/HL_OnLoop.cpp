//==============================================================================
#include "HardLight.h"
#include "MeshData.h"
#include "MeshMap.h"

vec3 oldPos = vec3(0.0f,1.0f,600.0f);
PxF32 gSteerVsForwardSpeedData[2*8]=
{
	0.0f,		0.75f,
	5.0f,		0.75f,
	30.0f,		0.75f,
	120.0f,		0.75f,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32,
	PX_MAX_F32, PX_MAX_F32
};
PxFixedSizeLookupTable<8> gSteerVsForwardSpeedTable(gSteerVsForwardSpeedData,4);

PxVehiclePadSmoothingData gPadSmoothingData=
{
	{
		6.0f,	//rise rate eANALOG_INPUT_ACCEL
		6.0f,	//rise rate eANALOG_INPUT_BRAKE		
		6.0f,	//rise rate eANALOG_INPUT_HANDBRAKE	
		2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT
		2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT
	},
	{
		10.0f,	//fall rate eANALOG_INPUT_ACCEL
		10.0f,	//fall rate eANALOG_INPUT_BRAKE		
		10.0f,	//fall rate eANALOG_INPUT_HANDBRAKE	
		5.0f,	//fall rate eANALOG_INPUT_STEER_LEFT
		5.0f	//fall rate eANALOG_INPUT_STEER_RIGHT
	}
};

//==============================================================================
void HardLight::OnLoop()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msPhysics < 1000 / 60) return;
	Uint32 elapsed = msCurrent - msPhysics;
	if (elapsed > msMax) elapsed = msMax;
	float timestep = elapsed / 1000.0f;

	PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs(gPadSmoothingData, gSteerVsForwardSpeedTable, bike->getInputData(), timestep, bike->isInAir(), *bike->getVehicle4W());

	//Raycasts.
	PxVehicleWheels* vehicles[1] = {bike->getVehicle4W()};
	PxRaycastQueryResult* raycastResults = bike->getVehicleSceneQueryData()->getRaycastQueryResultBuffer(0);
	const PxU32 raycastResultsSize = bike->getVehicleSceneQueryData()->getRaycastQueryResultBufferSize();
	PxVehicleSuspensionRaycasts(bike->getBatchQuery(), 1, vehicles, raycastResultsSize, raycastResults);

	//Vehicle update.
	const PxVec3 grav = gScene->getGravity();
	PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
	PxVehicleWheelQueryResult vehicleQueryResults[1] = {{wheelQueryResults, bike->getVehicle4W()->mWheelsSimData.getNbWheels()}};
	PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	//Work out if the vehicle is in the air.
	bike->setInAir(false);//gVehicle4W->getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);
	//gIsVehicleInAir = false;//gVehicle4W->getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);

	//Scene update.
	gScene->simulate(timestep);
	msPhysics = msCurrent;

	// tail creation

	PxTransform newPos = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
	vec3 dis = vec3(newPos.p.x,newPos.p.y,newPos.p.z);
	vec3 major = oldPos -dis;

	if(sqrt(major.x*major.x+major.y*major.y+major.z*major.z) > 1){
		//MeshMap::Instance()->getEntityMesh("Wall.obj")->CreateTail(oldPos,newPos,1);
		oldPos = dis;
		TailWall* Wall = new TailWall(gPhysics->createRigidStatic(newPos),MeshMap::Instance()->getEntityMesh("Wall.obj"),"../data/Textures/LightTrail.tga");
		world.add_entity(Wall);
	}

	while(!gScene->fetchResults() )
	{
		
	}
}

//==============================================================================

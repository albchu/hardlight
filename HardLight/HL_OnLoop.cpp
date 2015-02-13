//==============================================================================
#include "HardLight.h"

PxF32 gSteerVsForwardSpeedData[2*8]=
{
	0.0f,		0.75f,
	5.0f,		0.75f,
	30.0f,		0.125f,
	120.0f,		0.1f,
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

	//PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs(gPadSmoothingData, gSteerVsForwardSpeedTable, gVehicleInputData, timestep, gIsVehicleInAir, *gVehicle4W);

	////Raycasts.
	//PxVehicleWheels* vehicles[1] = {gVehicle4W};
	//PxRaycastQueryResult* raycastResults = gVehicleSceneQueryData->getRaycastQueryResultBuffer(0);
	//const PxU32 raycastResultsSize = gVehicleSceneQueryData->getRaycastQueryResultBufferSize();
	//PxVehicleSuspensionRaycasts(gBatchQuery, 1, vehicles, raycastResultsSize, raycastResults);

	////Vehicle update.
	//const PxVec3 grav = gScene->getGravity();
	//PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
	//PxVehicleWheelQueryResult vehicleQueryResults[1] = {{wheelQueryResults, gVehicle4W->mWheelsSimData.getNbWheels()}};
	//PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	////Work out if the vehicle is in the air.
	//gIsVehicleInAir = gVehicle4W->getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);

	//Scene update.
	gScene->simulate(timestep);
	msPhysics = msCurrent;

	while(!gScene->fetchResults() )
	{
		
	}
}

//==============================================================================

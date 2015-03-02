//==============================================================================
#include "HardLight.h"
#include "MeshData.h"
#include "MeshMap.h"
#include "Skybox.h"

PxF32 gSteerVsForwardSpeedData[2*8]=
{
	0.0f,		0.75f,
	5.0f,		0.45f,
	30.0f,		0.45f,
	120.0f,		0.45f,
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

	
	for (unsigned int j = 0; j < bikesToKill.size(); j++)
	{
		if (!bikesToKill[j]->invincible) {
			gScene->removeActor(*bikesToKill[j]->get_actor(), false);
			world.remove(bikesToKill[j]);
			bikes.kill_bike(bikesToKill[j]);
			sfxMix.PlaySoundEffect(1);
			bikesToKill[j]->set_actor(NULL);
		}
	}
	bikesToKill.clear();

	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msPhysics < 1000 / 60) return;
	Uint32 elapsed = msCurrent - msPhysics;
	if (elapsed > msMax) elapsed = msMax;
	float timestep = elapsed / 1000.0f;

	for(Bike* bike : bikes.get_all_bikes())
	{
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
		//bike->setInAir(false);//gVehicle4W->getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);
		//gIsVehicleInAir = false;//gVehicle4W->getRigidDynamicActor()->isSleeping() ? false : PxVehicleIsInAir(vehicleQueryResults[0]);
	//	cout << "Bike reference : " << bikes.get_bot_bikes()[0] << endl;
	//if(controller->get_bike()->get_actor() != NULL)
	//	controller->forward();
	}

	//for(Controller* controllable: controllableBikes)
	//{
	//	controllable->forward();
	//}


	//Scene update.
	gScene->simulate(timestep);
	msPhysics = msCurrent;

	// tail creation







	gScene->fetchResults(true);
}

//==============================================================================

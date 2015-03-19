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
	float closest_sound = FLT_MAX;

	// Delete all bikes queued up to be destroyed
	for (Bike* bikeX : bikesToKill)
	{
		if (!bikeX->get_chassis()->is_invincible())
		{
			for (Bike* bikeY : bike_manager->get_player_bikes())
				closest_sound = glm::min(closest_sound, bikeY->get_chassis()->get_distance(bikeX->get_chassis()));
			bike_manager->kill_bike(bikeX);
		}
	}
	if (closest_sound < FLT_MAX)
		sfxMix.PlaySoundEffect("sfxExplosion", closest_sound, 0);
	bikesToKill.clear();

	// Albert disabled this because he has no idea how it works and will refactor it anyways
	//closest_sound = FLT_MAX;
	//for (unsigned int i = 0; i < hit_pickup.size(); i++)
	//{
	//	PxRigidActor* pickup_actor = pickup_hit[i];
	//	Chassis* bike = hit_pickup[i];
	//	bike_manager->extend_tail(bike);
	//	for (unsigned int i = 0; i < bike_manager->get_player_bikes().size(); i++)
	//		closest_sound = glm::min(closest_sound, bike_manager->get_player_bikes()[i]->get_distance(pickup));
	//}
	if (hit_pickup.size() > 0)
	{
		sfxMix.PlaySoundEffect("sfxIntro", closest_sound, 0);
		hit_pickup.clear();
		pickup_hit.clear();
		pickup->respawn();
	}

	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msPhysics < 1000 / 60) return;
	Uint32 elapsed = msCurrent - msPhysics;
	if (elapsed > msMax) elapsed = msMax;
	float timestep = elapsed / 1000.0f;

	// Prepare all bikes in the world to move. Albert note: Try moving this to on_init
	for(Bike* bike : bike_manager->get_all_bikes())
	{
		Chassis* chassis = bike->get_chassis();
		PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs(gPadSmoothingData, gSteerVsForwardSpeedTable, chassis->getInputData(), timestep, chassis->isInAir(), *chassis->getVehicle4W());

		//Raycasts.
		PxVehicleWheels* vehicles[1] = {chassis->getVehicle4W()};
		PxRaycastQueryResult* raycastResults = chassis->getVehicleSceneQueryData()->getRaycastQueryResultBuffer(0);
		const PxU32 raycastResultsSize = chassis->getVehicleSceneQueryData()->getRaycastQueryResultBufferSize();
		PxVehicleSuspensionRaycasts(chassis->getBatchQuery(), 1, vehicles, raycastResultsSize, raycastResults);

		//Vehicle update.
		//const PxVec3 grav = pxAgent->get_scene()->getGravity();
		PxVec3 grav = PxVec3(0,1,0) * -gravity;
		if (map_type == MapTypes::SPHERE)
			grav = vehicles[0]->getRigidDynamicActor()->getGlobalPose().p.getNormalized() * -gravity;
		bike->getVehicle4W()->getRigidDynamicActor()->clearForce();
		bike->getVehicle4W()->getRigidDynamicActor()->addForce(grav, PxForceMode::eACCELERATION);
		vec3 forward = bike->get_direction_vector();
		PxVec3 slow = bike->getVehicle4W()->getRigidDynamicActor()->getLinearVelocity() * -dampening;
		//cout << bike->getVehicle4W()->getRigidDynamicActor()->getLinearVelocity().magnitude() << endl;
		bike->getVehicle4W()->getRigidDynamicActor()->addForce(slow, PxForceMode::eACCELERATION);

		PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
		PxVehicleWheelQueryResult vehicleQueryResults[1] = {{wheelQueryResults, chassis->getVehicle4W()->mWheelsSimData.getNbWheels()}};
		PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	}

	// Move Bot BikeManager
	overMind->update_bikes(pickup->get_location());
	overMind->move_bikes();

	// Tail creation
	for(Bike* bike : bike_manager->get_all_bikes())
	{
		bike->get_tail()->update(pxAgent);
	}

	// Check win/loss condition
	if(!config->GetBoolean("game", "debugMode", false))
	{
		//if(bike_manager->get_all_bikes().size() == 1)
		//{
		//	Chassis* aBike = bike_manager->get_all_bikes()[0];
		//	if(aBike->get_subtype() == PLAYER_BIKE)
		//	{
		//		menu->set_texture(TextureMap::Instance()->getTexture("../data/images/Win.tga"));
		//		scene = PAUSE;	// This is to avoid allowing the player to win, then kill themselves and have a loss screen show up.
		//	}
		//	if(aBike->get_subtype() == BOT_BIKE)
		//	{
		//		menu->set_texture(TextureMap::Instance()->getTexture("../data/images/Lose.tga"));
		//	}

		//	menu->set_renderable(true);
		//}
		//else if (bike_manager->get_player_bikes().size() == 0)
		//{
		//	menu->set_texture(TextureMap::Instance()->getTexture("../data/images/Lose.tga"));
		//	menu->set_renderable(true);
		//}
	}

	//Scene update.
	pxAgent->get_scene()->simulate(timestep);
	msPhysics = msCurrent;

	pxAgent->get_scene()->fetchResults(true);
}

//==============================================================================

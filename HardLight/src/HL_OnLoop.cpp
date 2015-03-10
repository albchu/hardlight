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
	for (unsigned int j = 0; j < bikesToKill.size(); j++)
	{
		if (!bikesToKill[j]->invincible) {
			pxAgent->get_scene()->removeActor(*bikesToKill[j]->get_actor(), false);
			for (unsigned int i = 0; i < bike_manager->get_player_bikes().size(); i++)
				closest_sound = glm::min(closest_sound, bike_manager->get_player_bikes()[i]->get_distance(bikesToKill[j]));
			bike_manager->kill_bike(bikesToKill[j]);
		}

	}
	if (closest_sound < FLT_MAX)
		sfxMix.PlaySoundEffect("sfxExplosion", closest_sound, 0);
	bikesToKill.clear();

	closest_sound = FLT_MAX;
	for (unsigned int i = 0; i < hit_pickup.size(); i++)
	{
		PxRigidActor* pickup_actor = pickup_hit[i];
		Chassis* bike = hit_pickup[i];
		bike_manager->extend_tail(bike);
		for (unsigned int i = 0; i < bike_manager->get_player_bikes().size(); i++)
			closest_sound = glm::min(closest_sound, bike_manager->get_player_bikes()[i]->get_distance(pickup));
	}
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

	for(Chassis* bike : bike_manager->get_all_bikes())
	{
		PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs(gPadSmoothingData, gSteerVsForwardSpeedTable, bike->getInputData(), timestep, bike->isInAir(), *bike->getVehicle4W());

		//Raycasts.
		PxVehicleWheels* vehicles[1] = {bike->getVehicle4W()};
		PxRaycastQueryResult* raycastResults = bike->getVehicleSceneQueryData()->getRaycastQueryResultBuffer(0);
		const PxU32 raycastResultsSize = bike->getVehicleSceneQueryData()->getRaycastQueryResultBufferSize();
		PxVehicleSuspensionRaycasts(bike->getBatchQuery(), 1, vehicles, raycastResultsSize, raycastResults);

		//Vehicle update.
		const PxVec3 grav = pxAgent->get_scene()->getGravity();
		PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
		PxVehicleWheelQueryResult vehicleQueryResults[1] = {{wheelQueryResults, bike->getVehicle4W()->mWheelsSimData.getNbWheels()}};
		PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

	}

	// Move Bot BikeManager
	overMind->update_bikes(pickup->get_location());
	overMind->move_bikes();

	// Tail creation
	for(TailWall* tail_wall : bike_manager->get_all_tails())
	{
		tail_wall->update(pxAgent);
	}

	// Check win/loss condition
	if(!config->GetBoolean("game", "debugMode", false))
	{
		if(bike_manager->get_all_bikes().size() == 1)
		{
			Chassis* aBike = bike_manager->get_all_bikes()[0];
			if(aBike->get_subtype() == PLAYER_BIKE)
			{
				menu->set_texture(TextureMap::Instance()->getTexture("../data/images/Win.tga"));
				scene = PAUSE;	// This is to avoid allowing the player to win, then kill themselves and have a loss screen show up.
			}
			if(aBike->get_subtype() == BOT_BIKE)
			{
				menu->set_texture(TextureMap::Instance()->getTexture("../data/images/Lose.tga"));
			}

			menu->set_renderable(true);
		}
		else if (bike_manager->get_player_bikes().size() == 0)
		{
			menu->set_texture(TextureMap::Instance()->getTexture("../data/images/Lose.tga"));
			menu->set_renderable(true);
		}
	}

	//Scene update.
	pxAgent->get_scene()->simulate(timestep);
	msPhysics = msCurrent;

	pxAgent->get_scene()->fetchResults(true);
}

//==============================================================================

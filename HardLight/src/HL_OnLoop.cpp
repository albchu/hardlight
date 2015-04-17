//==============================================================================
#include "HardLight.h"
#include "MeshData.h"
#include "MeshMap.h"
#include "Skybox.h"

PxF32 gSteerVsForwardSpeedData[2*8]=
{
	0.0f,		0.35f,
	5.0f,		0.35f,
	30.0f,		0.35f,
	120.0f,		0.35f,
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
	//if (msCurrent - msPhysics < 1000 / 60)
	//{
	//	cout << "On loop returned" << endl;
	//	return;
	//}
	Uint32 elapsed = msCurrent - msPhysics;
	if (elapsed > msMax) 
		elapsed = msMax;
	float timestep = elapsed / 1000.0f;
	if(timestep < 0.001)
		timestep = 0.001;
	float closest_sound = FLT_MAX;

	// Delete all bikes queued up to be destroyed
	if(deathCalc->ready())
	{
		for (Bike* bikeX : bikesToKill)
		{
			if (!bikeX->get_chassis()->is_invincible())
			{
				if(bikeX->get_subtype() == PLAYER_BIKE)
				{
					((Player_Controller*)bikeX->get_controller())->rumble(1.0, 220);
				}

				for (Bike* bikeY : bike_manager->get_player_bikes())
					closest_sound = glm::min(closest_sound, bikeY->get_chassis()->get_distance(bikeX->get_chassis()));
				bike_manager->kill_bike(bikeX);

				PxVec3 collisionPosition = PxVec3(bikeX->get_chassis()->get_actor()->getGlobalPose().p);
				// initialize creation data: random velocities and directions
				particleCreationData = ParticleFactory::createRandomParticleData(maxParticles, particleSpeed, &particleData, collisionPosition);
				// initialize particle system
				particleSystem = ParticleFactory::createParticles(maxParticles, pxAgent->get_physics(), particleCreationData);

				// add to scene
				if(particleSystem)
					pxAgent->get_scene()->addActor(*particleSystem);

				ParticleSystem* particleEntity = new ParticleSystem(pxAgent->get_physics()->createRigidStatic(PxTransform(PxVec3(0.0f, 5.0f, 0.0f))), ParticleFactory::createMeshData(particleSystem), bikeX->get_tail()->get_texture(), SDL_GetTicks());
				particleEntity->setParticleSystem(particleSystem);
				particleEntity->setParticleData(particleData);
				world.add_entity(particleEntity);
			}
		}
		if (closest_sound < FLT_MAX)
			sfxMix.PlaySoundEffect("sfxExplosion", closest_sound, 0);
		bikesToKill.clear();
	}

	// Process all powerups that were hit. Note: Cannot be done in OnTrigger because physx complains
	if(powerupCalc->ready())
	{
		for(tuple<Bike*,PxRigidActor*> pair : bikePowerupPairs)
		{
			powerup_manager->apply_powerup(get<0>(pair), get<1>(pair));
		}
		bikePowerupPairs.clear();
	}

	// Prepare all bikes in the world to move. 
	for(Bike* bike : bike_manager->get_all_bikes())
	{
		if(bike->is_renderable())
		{
			Chassis* chassis = bike->get_chassis();
			PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs(gPadSmoothingData, gSteerVsForwardSpeedTable, chassis->getInputData(), timestep, chassis->isInAir(), *chassis->getVehicle4W());

			//Raycasts.
			PxVehicleWheels* vehicles[1] = {chassis->getVehicle4W()};
			PxRaycastQueryResult* raycastResults = chassis->getVehicleSceneQueryData()->getRaycastQueryResultBuffer(0);
			const PxU32 raycastResultsSize = chassis->getVehicleSceneQueryData()->getRaycastQueryResultBufferSize();
			PxVehicleSuspensionRaycasts(chassis->getBatchQuery(), 1, vehicles, raycastResultsSize, raycastResults);

			//Vehicle update.
			PxRigidDynamic* actor = chassis->getVehicle4W()->getRigidDynamicActor();
			if (map_type == MapTypes::SPHERE)
				bike->set_gravity_up(actor->getGlobalPose().p);
			PxVec3 grav = bike->get_gravity_up() * -gravity;
			//increase gravity with forward speed
			if (map_type != MapTypes::PLANE)
				grav += (bike->get_gravity_up() * -1.f * actor->getLinearVelocity().magnitude());
			actor->clearForce();
			actor->addForce(grav, PxForceMode::eACCELERATION);

			PxWheelQueryResult wheelQueryResults[PX_MAX_NB_WHEELS];
			PxVehicleWheelQueryResult vehicleQueryResults[1] = {{wheelQueryResults, chassis->getVehicle4W()->mWheelsSimData.getNbWheels()}};
			PxVehicleUpdates(timestep, grav, *gFrictionPairs, 1, vehicles, vehicleQueryResults);

		}
	}

	for(Entity* entity : world.getEntities()) {
		// check for old particle systems
		if(entity->get_type() == PARSYSTEM) {
			ParticleSystem* p = (ParticleSystem*)entity;
			if(p->isOld(msCurrent, explosionLifeSpan)) {
				world.remove(p);
			}
		}
	}

	// Move Bot BikeManager
	overMind->update_bikes(powerup_manager);
	overMind->move_bikes();

	// Tail creation
	for(Bike* bike : bike_manager->get_all_bikes())
	{
		bike->get_tail()->update(pxAgent);
	}

	if(powerupCalc->ready())
	{
		// Rotate powerups
		powerup_manager->rotate_all();
	}

	// Update all timed powerups
	for(Bike* bike : bike_manager->get_all_bikes())
	{
		bike->check_ghost_powerup();
		bike->check_super_saiyen_powerup();
	}

	// Update scoreboard
	scoreboard.update_scoreboard();

	// Check win/loss condition
	if(winCalc->ready() && scene == GAME && !config->GetBoolean("game", "debugMode", false))
	{
		for(Bike* bike : bike_manager->get_all_bikes())
		{
			if(bike->get_player_score() >= 5)
			{
				for(unsigned int i = 0; i < viewports.size(); i++) 
				{
					if(bike->get_id() == viewports[i].id)
					{
						viewports[i].message = "You Win!";
					}
					else 
					{
						viewports[i].message = "You Lost!";
					}
				}
				scene = GAME_OVER;
			}
		}
		if(bike_manager->get_all_bikes().size() - bike_manager->get_dead_bikes().size() == 1)
		{
			Bike* aBike;
			for(Bike* bike : bike_manager->get_all_bikes())
			{
				if(bike->is_renderable())
					aBike = bike;
			}
			//Bike* aBike = bike_manager->get_all_bikes()[0];
			for(unsigned int i = 0; i < viewports.size(); i++) {
				if(aBike->get_id() == viewports[i].id) {
					viewports[i].message = "You Win!";
				}
				else {
					viewports[i].message = "You Lost!";
				}
			}
			scene = GAME_OVER;
		}
		else if (bike_manager->get_all_bikes().size() == bike_manager->get_dead_bikes().size())
		{
			for(unsigned int i = 0; i < viewports.size(); i++) {
				viewports[i].message = "You Lost!";
			}
			scene = GAME_OVER;
		}

	}

	//Scene update.
	pxAgent->get_scene()->simulate(timestep);
	msPhysics = msCurrent;

	pxAgent->get_scene()->fetchResults(true);
}

//==============================================================================

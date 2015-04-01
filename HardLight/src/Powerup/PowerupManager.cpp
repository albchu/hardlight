#include "Powerup/PowerupManager.h"
#include "Common.h"

PowerupManager::PowerupManager(World* new_world, INIReader* config, PhysxAgent* new_pxAgent, SoundMixer* new_sfxMix)
{
	pxAgent = new_pxAgent;
	world = new_world;
	sfxMix = new_sfxMix;

	// Initialize all powers lists
	all_hold_powers.push_back(&Hold::jump);
	all_hold_powers.push_back(&Hold::ghost);
	all_hold_powers.push_back(&Hold::super_saiyen);

	all_instant_powers.push_back(&Instant::extendTail);

	scaleFactors = vec3(10.0f, 10.0f, 10.0f);

	maxPickups = config->GetInteger("powerup", "maxPickups", 1);
	heightOffFloor = (float)config->GetReal("powerup", "heightOffFloor", 0.0f);
	mapType = config->GetInteger("scene", "map", MapTypes::SPHERE);
	arena_size = (float)config->GetReal("scene", "size", 300.0) - 20.0f;
}

PowerupManager::~PowerupManager()
{
	all_hold_powers.clear();
	all_hold_powers.shrink_to_fit();
	all_instant_powers.clear();
	all_instant_powers.shrink_to_fit();
}

// Spawns some random powerup in some random place. NOTE: Currently unimplemented because thinking of way to handle sphere map
void PowerupManager::spawn_random_powerup()
{
	if(mapType == MapTypes::SPHERE)
	{
		spawn_random_powerup(vec3(Common::getRandFloat(-arena_size, arena_size), arena_size + heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
	}
	else if (mapType == MapTypes::PLANE)
	{
		spawn_random_powerup(vec3(Common::getRandFloat(-arena_size, arena_size), heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
	}
	else
		cerr << "Do not understand how to generate powerups on this map type" << endl;
}


void PowerupManager::spawn_hold_powerup(vec3 position)
{
	//cout << "Spawned a new hold powerup at " << glm::to_string(position) << endl;
	PxRigidActor* actor = pxAgent->create_pickup(position, vec3(0,1,0), scaleFactors);
	actor->setName("HOLD");
	Entity* powerup = new HoldEntity(all_hold_powers[rand() % all_hold_powers.size()], actor, scaleFactors);
	holdEntities.push_back((HoldEntity*)powerup);
	world->add_entity(powerup);
}

void PowerupManager::spawn_hold_powerup()
{
	if(mapType == MapTypes::SPHERE)
	{
		spawn_hold_powerup(vec3(Common::getRandFloat(-arena_size, arena_size), arena_size + heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
	}
	else if (mapType == MapTypes::PLANE)
	{
		spawn_hold_powerup(vec3(Common::getRandFloat(-arena_size, arena_size), heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
	}
	else
		cerr << "Do not understand how to generate powerups on this map type" << endl;
}

void PowerupManager::spawn_instant_powerup()
{
	if(mapType == MapTypes::SPHERE)
	{
		spawn_instant_powerup(vec3(Common::getRandFloat(-arena_size, arena_size), arena_size + heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
	}
	else if (mapType == MapTypes::PLANE)
	{
		spawn_instant_powerup(vec3(Common::getRandFloat(-arena_size, arena_size), heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
	}
	else
		cerr << "Do not understand how to generate powerups on this map type" << endl;
}
void PowerupManager::spawn_instant_powerup(vec3 position)
{
	//cout << "Spawned a new instant powerup at " << glm::to_string(position) << endl;
	PxRigidActor* actor = pxAgent->create_pickup(position, vec3(0,1,0), scaleFactors);
	actor->setName("INSTANT");
	Entity* powerup = new InstantEntity(all_instant_powers[rand() % all_instant_powers.size()], actor, scaleFactors);
	instantEntities.push_back((InstantEntity*)powerup);
	world->add_entity(powerup);
}

// Rotate all powerup entities on the map
void PowerupManager::rotate_all()
{
	glm::vec3 rot(0, 2.0*(float)M_PI/180.0, 0);
	for(HoldEntity* holdEntity : holdEntities)
	{
		PxTransform pose = holdEntity->get_actor()->getGlobalPose();
		glm::quat aQuat(pose.q.w, pose.q.x, pose.q.y, pose.q.z);
		glm::quat done = glm::normalize(aQuat * glm::quat(rot));
		holdEntity->get_actor()->setGlobalPose(PxTransform(pose.p.x, pose.p.y, pose.p.z, PxQuat(done.x, done.y, done.z, done.w)));
	}
	for(InstantEntity* instantEntity : instantEntities)
	{
		PxTransform pose = instantEntity->get_actor()->getGlobalPose();
		glm::quat aQuat(pose.q.w, pose.q.x, pose.q.y, pose.q.z);
		glm::quat done = glm::normalize(aQuat * glm::quat(rot));
		instantEntity->get_actor()->setGlobalPose(PxTransform(pose.p.x, pose.p.y, pose.p.z, PxQuat(done.x, done.y, done.z, done.w)));
	}
}

// Spawns a brand new powerup and adds it to the list of powerups in play
void PowerupManager::spawn_random_powerup(vec3 position)
{
	// Random chance to determine what kind of powerup to build
	if(rand() % 10 < 9)
	{
		spawn_hold_powerup(position);
	}
	else
	{
		spawn_instant_powerup(position);
	}
}

// Applies the selected powerup to a bike
void PowerupManager::apply_powerup(Bike* bike, PxRigidActor* powerup_actor)
{
	if(bike->get_subtype() == PLAYER_BIKE)
	{
		((Player_Controller*)bike->get_controller())->rumble(1.0, 155);
	}

	if(powerup_actor->getName() == "HOLD")
	{
		//cout << "Applying hold powerup" << endl;
		if(bike->get_subtype() == PLAYER_BIKE) sfxMix->PlaySoundEffect("sfxPowerupReady");
		HoldEntity* holdEntity = getHoldEntity(powerup_actor);
		
		// If we find a match, we will apply the powerup
		if(holdEntity != NULL)
		{
			int i;
			for (i=0; i<all_hold_powers.size(); i++)
			{
				if (all_hold_powers[i] == holdEntity->get_powerup())
					break;
			}
			bike->set_hold_powerup(holdEntity->get_powerup(), i);
			respawn_powerup(holdEntity);
		}
	}
	else if(powerup_actor->getName() == "INSTANT")
	{
		//cout << "Applying instant powerup" << endl;
		if(bike->get_subtype() == PLAYER_BIKE) sfxMix->PlaySoundEffect("sfxPowerupInstant");
		InstantEntity* instantEntity = getInstantEntity(powerup_actor);

		// If we find a match, we will apply the powerup
		if(instantEntity != NULL)
		{
			bike->execute_instant_powerup(instantEntity->get_powerup());
			respawn_powerup(instantEntity);
		}
	}
}

HoldEntity* PowerupManager::getHoldEntity(PxRigidActor* holdActor)
{
	for(HoldEntity* holdEntity : holdEntities)
	{
		if(holdActor == holdEntity->get_actor())
			return holdEntity;
	}
	return NULL;
}

InstantEntity* PowerupManager::getInstantEntity(PxRigidActor* instantActor)
{
	for(InstantEntity* instantEntity : instantEntities)
	{
		if(instantActor == instantEntity->get_actor())
			return instantEntity;
	}
	return NULL;
}

// Moves an existing powerup to a new spot on the map and updates its power
void PowerupManager::respawn_powerup(HoldEntity* holdEntity)
{
	// Set new hold power to anything 
	holdEntity->set_powerup(all_hold_powers[Common::getRandInt(0, all_hold_powers.size())]);

	// Move the entity
	holdEntity->get_actor()->setGlobalPose(PxTransform(Common::getRandFloat(-arena_size, arena_size), heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
}

void PowerupManager::respawn_powerup(InstantEntity* instantEntity)
{
	// Set new hold power to anything 
	instantEntity->set_powerup(all_instant_powers[rand() % all_instant_powers.size()]);

	// Move the entity
	instantEntity->get_actor()->setGlobalPose(PxTransform(Common::getRandFloat(-arena_size, arena_size), heightOffFloor, Common::getRandFloat(-arena_size, arena_size)));
}

vector<HoldEntity*> PowerupManager::get_all_hold_entities()
{
	return holdEntities;
}

vector<InstantEntity*> PowerupManager::get_all_instant_entities()
{
	return instantEntities;
}


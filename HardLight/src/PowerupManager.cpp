#include "PowerupManager.h"

PowerupManager::PowerupManager(World* new_world, INIReader* config, PhysxAgent* new_pxAgent)
{
	pxAgent = new_pxAgent;
	world = new_world;

	srand ((unsigned int)time(NULL));	// Seed for random value generator

	// Initialize all powers lists
	all_hold_powers.push_back(&Hold::jump);

	all_instant_powers.push_back(&Instant::extendTail);

	scaleFactors = vec3(10.0f, 10.0f, 10.0f);

	maxPickups = config->GetInteger("pickup", "maxPickups", 1);
	heightOffFloor = (float)config->GetReal("pickup", "heightOffFloor", 0.0f);
}

PowerupManager::~PowerupManager()
{
	all_hold_powers.clear();
	all_hold_powers.shrink_to_fit();
	all_instant_powers.clear();
	all_instant_powers.shrink_to_fit();
}

void PowerupManager::spawn_random_powerup()
{

}

// Spawns a brand new powerup and adds it to the list of powerups in play
void PowerupManager::spawn_random_powerup(vec3 position)
{
	PxRigidActor* actor = pxAgent->create_pickup(position, vec3(0,1,0), scaleFactors);
	actor->setName("HOLD");
	HoldEntity* powerup = new HoldEntity(all_hold_powers[0], actor);
	world->add_entity(powerup);
	holdEntities.push_back(powerup);
}

// Applies the selected powerup to a bike
void PowerupManager::apply_powerup(Bike* bike, PxRigidActor* powerup_actor)
{
	if(powerup_actor->getName() == "HOLD")
	{
		cout << "Applying hold powerup" << endl;
		HoldEntity* holdEntity = getHoldEntity(powerup_actor);

		// If we find a match, we will apply the powerup
		if(holdEntity != NULL)
		{
			respawn_powerup(holdEntity);
		}
	}
	else if(powerup_actor->getName() == "INSTANT")
	{
		cout << "Applying instant powerup" << endl;

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

void PowerupManager::respawn_powerup(HoldEntity* holdEntity)
{
	// Set new hold power to anything 
	holdEntity->set_powerup(all_hold_powers[rand() % all_hold_powers.size()]);

	// Move the entity
	holdEntity->get_actor()->setGlobalPose(PxTransform(rand() % 100, heightOffFloor, rand() % 100));
}

void PowerupManager::respawn_powerup(InstantEntity* instantEntity)
{

}



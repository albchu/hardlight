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
	HoldEntity* powerup = new HoldEntity(all_hold_powers[0], actor);
	world->add_entity(powerup);
	holdEntities.push_back(powerup);
}

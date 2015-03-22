#include "PowerupManager.h"

PowerupManager::PowerupManager()
{
	srand ((unsigned int)time(NULL));	// Seed for random value generator

	// Initialize all powers lists
	all_hold_powers.push_back(&Hold::jump);

	all_instant_powers.push_back(&Instant::extendTail);
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

void PowerupManager::spawn_random_powerup(PxVec3 position)
{

}

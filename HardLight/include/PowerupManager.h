#ifndef _POWERUP_ITEM_H
#define _POWERUP_ITEM_H

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Powerup.h"
#include "Hold.h"
#include "Instant.h"
#include "HoldEntity.h"
#include "InstantEntity.h"
#include "World.h"
#include "Vehicle/Bike.h"

using namespace std;

// Manages all powerups in the world
class PowerupManager
{
public:
	//typedef void (Powerup::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config);
	PowerupManager(World* new_world, INIReader* config, PhysxAgent* new_pxAgent);
	void spawn_random_powerup();
	void respawn_powerup(HoldEntity* holdEntity);
	void respawn_powerup(InstantEntity* instantEntity);
	void spawn_random_powerup(vec3 position);
	void apply_powerup(Bike* bike, PxRigidActor* powerup_actor);
	~PowerupManager();

private:
	vector<Powerup<Hold>::PowerCallback> all_hold_powers;
	vector<Powerup<Instant>::PowerCallback> all_instant_powers;
	vector<HoldEntity*> holdEntities;
	vector<InstantEntity*> instantEntities;
	PhysxAgent* pxAgent;
	World* world;
	float heightOffFloor;
	vec3 scaleFactors;
	float arena_size;
	int maxPickups;
	
	HoldEntity* getHoldEntity(PxRigidActor* holdActor);
	InstantEntity* getInstantEntity(PxRigidActor* instantActor);
};


#endif
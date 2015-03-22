#ifndef _POWERUP_ITEM_H
#define _POWERUP_ITEM_H

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "Powerup.h"
#include "Hold.h"
#include "Instant.h"
#include "HoldEntity.h"
#include "World.h"

using namespace std;

// Manages all powerups in the world
class PowerupManager
{
public:
	//typedef void (Powerup::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config);
	PowerupManager(World* new_world, INIReader* config, PhysxAgent* new_pxAgent);
	void spawn_random_powerup();
	void spawn_random_powerup(vec3 position);
	~PowerupManager();

private:
	vector<Powerup<Hold>::PowerCallback> all_hold_powers;
	vector<Powerup<Instant>::PowerCallback> all_instant_powers;
	vector<HoldEntity*> holdEntities;
	PhysxAgent* pxAgent;
	World* world;
	float heightOffFloor;
	vec3 scaleFactors;
	float arena_size;
	int maxPickups;
};


#endif
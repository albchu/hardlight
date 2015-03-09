#ifndef _PICKUP_H
#define _PICKUP_H



#include "Entity.h"
#include "World.h"
#include "Vehicle\Bikes.h"
#include "Powerup.h"

#include "../inih\cpp\INIReader.h"

class Pickup : public Entity
{
public:
	Pickup();
	Pickup(World* world, INIReader* config, PhysxAgent* pxAgent);
	~Pickup();

	bool placePickup();
	Powerup* givePowerup();
private:
	World *world;

	int maxPickups;
	float heightOffFloor;

	vector<bool> hasPowerup; // lists whether a bike has one powerup or no powerups
	vector<Powerup*> bikePowerups; // list of the powerup allocated to each bike
};
#endif
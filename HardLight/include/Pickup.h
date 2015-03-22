#ifndef _PICKUP_H
#define _PICKUP_H



#include "Entity.h"
#include "World.h"
#include "Vehicle\BikeManager.h"
#include "Powerup.h"

#include "../inih\cpp\INIReader.h"
//DEPRECIATED>> NO LONGER BEING USED
class Pickup : public Entity
{
public:
	Pickup(INIReader* config, PhysxAgent* pxAgent, float arena_size);

	bool placePickup();
	//Powerup* givePowerup();
	
	virtual mat4 get_model_matrix();
	void respawn();
	vec3 get_position();

private:
	float random_float(float low, float high);
	float border;
	int maxPickups;
	float heightOffFloor;
	vec3 scaleFactors;
	float arena_size;

	vector<bool> hasPowerup; // lists whether a bike has one powerup or no powerups
	//vector<Powerup*> bikePowerups; // list of the powerup allocated to each bike
};
#endif
#ifndef _POWERUP_H
#define _POWERUP_H

#include "PowerupTypes.h"
#include "Vehicle\Bike.h"
#include "Vehicle\Bikes.h"
#include "Vehicle\TailWall.h"

class Powerup
{
public:
	Powerup();
	Powerup(Bike* bike, Bikes* bikes);
	~Powerup();

	Bike* getBike();
	Bikes* getBikes();
	PowerupTypes getPowerType();

	void setBike(Bike* bike);
	void setBikes(Bikes* bikes);
	void setPowerType(PowerupTypes powType);

	void choosePowerup(); // determine the type of powerup the Powerup object will be
	void choosePowerup(PowerupTypes powType);
	void allocatePowerup(); // assign a powerup to a bike
	void usePowerup(); // tell bike to use a powerup (generic version)

private:
	Bike* bike;
	Bikes* bikes;

	PowerupTypes powType;

	// Specific usePowerup functions
	void useExtendTail();
	void useJump();
	void useInvincible();
};
#endif
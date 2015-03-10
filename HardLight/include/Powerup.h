#ifndef _POWERUP_H
#define _POWERUP_H

#include "PowerupTypes.h"
#include "Vehicle\Bike.h"
#include "Vehicle\BikeManager.h"
#include "Vehicle\TailWall.h"

#include "../inih\cpp\INIReader.h"

class Powerup
{
public:
	Powerup();
	Powerup(Bike* bike, BikeManager* bikes, INIReader* config);
	~Powerup();

	Bike* getBike();
	BikeManager* getBikes();
	INIReader* getINIReader();
	PowerupTypes getPowerType();

	void setBike(Bike* bike);
	void setBikes(BikeManager* bikes);
	void setINIReader(INIReader* config);
	void setPowerType(PowerupTypes powType);

	void choosePowerup(); // determine the type of powerup the Powerup object will be
	int usePowerup(); // tell bike to use a powerup (generic version)

private:
	Bike* bike;
	BikeManager* bikes;

	INIReader* config;

	PowerupTypes powType;

	// Specific usePowerup functions
	void useExtendTail();
	void useJump();
	void useInvincible();
};
#endif
#ifndef _POWERUP_H
#define _POWERUP_H
#include "Vehicle\Chassis.h"
#include "Vehicle\TailWall.h"
//#include "Vehicle\BikeManager.h"
//#include "Vehicle\TailWall.h"

#include "../inih\cpp\INIReader.h"

enum PowerupUsage
{
	INSTANT,
	HOLD
};

class Powerup
{
public:
	Powerup();
	//Powerup(Bike* bike, BikeManager* bike_manager, INIReader* config);
	~Powerup();

	//Bike* getBike();
	//BikeManager* getBikes();
	//INIReader* getINIReader();

	//void setBike(Bike* bike);
	//void setBikes(BikeManager* bike_manager);
	//void setINIReader(INIReader* config);

	//void choosePowerup(); // determine the type of powerup the Powerup object will be
	//int usePowerup(); // tell bike to use a powerup (generic version)

private:

protected:
	PowerupUsage type;
	//Bike* bike;
	//BikeManager* bike_manager;

	//INIReader* config;


	//// Specific usePowerup functions
	//void useExtendTail();
	//void useJump();
};
#endif
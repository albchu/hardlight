#ifndef _HOLD_H
#define _HOLD_H

#include "Powerup.h"
//#include "Vehicle\Bike.h"
//This class contains all the powerups that the player will hold to trigger at their discression
class Hold : public Powerup
{
public:
	Hold();
	//~Hold();
	
	// Powerups
	void jump(Chassis* chassis, TailWall* tailwall, INIReader* config);

private:

};

#endif
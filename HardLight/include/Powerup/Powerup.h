#ifndef _POWERUP_H
#define _POWERUP_H
#include "Vehicle\Chassis.h"
#include "Vehicle\TailWall.h"

#include "../inih\cpp\INIReader.h"

template <class T> class Powerup
{
public:
	typedef void (T::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config);
};
#endif
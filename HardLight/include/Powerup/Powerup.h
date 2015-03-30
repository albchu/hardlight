#ifndef _POWERUP_H
#define _POWERUP_H
#include "Vehicle\Chassis.h"
#include "Vehicle\TailWall.h"

#include "../inih\cpp\INIReader.h"

#include <time.h>

struct PowerupTimers
{
	// Variables needed for timed powerups
	clock_t ghost_timer;
	bool using_ghost;
	clock_t super_saiyen_timer;
	bool using_super_saiyen;
};

template <class T> class Powerup
{
public:
	typedef void (T::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config, PowerupTimers* powerup_timers);
};
#endif
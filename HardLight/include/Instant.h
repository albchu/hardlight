#ifndef _INSTANT_H
#define _INSTANT_H

#include "Powerup.h"

class Instant : public Powerup
{
public:
	Instant();
	~Instant();
	void extendTail(Chassis* chassis, TailWall* tailwall, INIReader* config);
private:
};

#endif
#ifndef _HOLD_ENTITY_H
#define _HOLD_ENTITY_H

#include "Entity.h"
#include "Hold.h"

// This class represents a game world item containing a powerup ability
class HoldEntity : public Entity
{
public:
	//typedef void (Powerup::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config);
	HoldEntity(Powerup<Hold>::PowerCallback new_power, PxRigidActor* init_actor);
	~HoldEntity();
	Powerup<Hold>::PowerCallback get_powerup();

private:
	Powerup<Hold>::PowerCallback powerup; // The actual powerup attached to this item
};


#endif
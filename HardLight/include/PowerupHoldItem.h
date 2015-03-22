#ifndef _POWERUP_HOLD_ITEM_H
#define _POWERUP_HOLD_ITEM_H

#include "Entity.h"
#include "Hold.h"

// This class represents a game world item containing a powerup ability
class PowerupHoldItem : public Entity
{
public:
	//typedef void (Powerup::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config);
	PowerupHoldItem(Powerup<Hold>::PowerCallback new_power, PxRigidActor* init_actor);
	~PowerupHoldItem();
	Powerup<Hold>::PowerCallback get_powerup();

private:
	Powerup<Hold>::PowerCallback powerup; // The actual powerup attached to this item
};


#endif
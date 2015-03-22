#ifndef _POWERUP_ITEM_H
#define _POWERUP_ITEM_H

#include "Entity.h"
#include "Instant.h"

// This class represents a game world item containing a powerup ability
class PowerupInstantItem : public Entity
{
public:
	//typedef void (Powerup::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config);
	PowerupInstantItem(Powerup<Instant>::PowerCallback new_power, PxRigidActor* init_actor);
	~PowerupInstantItem();
	Powerup<Instant>::PowerCallback get_powerup();
	virtual mat4 get_model_matrix();

private:
	Powerup<Instant>::PowerCallback powerup; // The actual powerup attached to this item
};


#endif
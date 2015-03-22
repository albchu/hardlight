#ifndef _INSTANT_ENTITY_H
#define _INSTANT_ENTITY_H

#include "Entity.h"
#include "Instant.h"

// This class represents a game world item containing a powerup ability
class InstantEntity : public Entity
{
public:
	//typedef void (Powerup::*PowerCallback)(Chassis* chassis, TailWall* tailwall, INIReader* config);
	InstantEntity(Powerup<Instant>::PowerCallback new_power, PxRigidActor* init_actor);
	~InstantEntity();
	Powerup<Instant>::PowerCallback get_powerup();
	virtual mat4 get_model_matrix();

private:
	Powerup<Instant>::PowerCallback powerup; // The actual powerup attached to this item
};


#endif
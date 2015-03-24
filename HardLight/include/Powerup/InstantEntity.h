#ifndef _INSTANT_ENTITY_H
#define _INSTANT_ENTITY_H

#include "Entity.h"
#include "Powerup/Instant.h"

// This class represents a game world item containing a powerup ability
class InstantEntity : public Entity
{
public:
	InstantEntity(Powerup<Instant>::PowerCallback new_power, PxRigidActor* init_actor, vec3 new_scaleFactors);
	~InstantEntity();
	Powerup<Instant>::PowerCallback get_powerup();
	void set_powerup(Powerup<Instant>::PowerCallback new_power);
	virtual mat4 get_model_matrix();

private:
	Powerup<Instant>::PowerCallback powerup; // The actual powerup attached to this item
	vec3 scaleFactors;
};


#endif
#ifndef _HOLD_ENTITY_H
#define _HOLD_ENTITY_H

#include "Entity.h"
#include "Hold.h"

// This class represents a game world item containing a powerup ability
class HoldEntity : public Entity
{
public:
	HoldEntity(Powerup<Hold>::PowerCallback new_power, PxRigidActor* init_actor, vec3 new_scaleFactors);
	~HoldEntity();
	Powerup<Hold>::PowerCallback get_powerup();
	void set_powerup(Powerup<Hold>::PowerCallback new_power);
	virtual mat4 get_model_matrix();

private:
	Powerup<Hold>::PowerCallback powerup; // The actual powerup attached to this item
	vec3 scaleFactors;
};


#endif
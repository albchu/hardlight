
#ifndef _PARTICLESYSTEMENTITY_H_
#define _PARTICLESYSTEMENTITY_H_

#include "Entity.h"

class ParticleSystemEntity : public Entity {
private:

	physx::PxParticleSystem* particleSystem;

public:
	ParticleSystemEntity();
	ParticleSystemEntity();
};

#endif
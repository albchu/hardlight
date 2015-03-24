
#ifndef _PARTICLEFACTORY_H_
#define _PARTICLEFACTORY_H_

#include "Hardlight.h"

class ParticleFactory {
public:

	static PxParticleSystem* createParticles(int, PhysxAgent, PxParticleCreationData);
	static PxParticleCreationData createParticleData(int, ParticleData*, vec3, vec3, vec3);
};

#endif
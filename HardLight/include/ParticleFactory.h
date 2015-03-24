
#ifndef _PARTICLEFACTORY_H_
#define _PARTICLEFACTORY_H_

#include "ParticleData.h"
#include "PhysxAgent.h"

class ParticleFactory {
public:

	static PxParticleSystem* createParticles(int, PxPhysics*, physx::PxParticleCreationData);
	static PxParticleCreationData createParticleData(int, ParticleData*, PxVec3, PxVec3, PxVec3);
};

#endif
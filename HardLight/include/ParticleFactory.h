
#ifndef _PARTICLEFACTORY_H_
#define _PARTICLEFACTORY_H_

#include "MeshData.h"
#include "ParticleData.h"
#include "PhysxAgent.h"

class ParticleFactory {
public:

	static PxParticleSystem* createParticles(int, PxPhysics*, PxParticleCreationData);
	static PxParticleCreationData createRandomParticleData(int, float, ParticleData*, PxVec3);
	static MeshData* createMeshData(PxParticleSystem*);
};

#endif
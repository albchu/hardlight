
#ifndef _PARTICLEFACTORY_H_
#define _PARTICLEFACTORY_H_

#include "MeshData.h"
#include "ParticleData.h"
#include "PhysxAgent.h"

class ParticleFactory {
public:

	static PxParticleSystem* createParticles(int, PxPhysics*, physx::PxParticleCreationData);
	static PxParticleCreationData createParticleData(int, ParticleData*, PxVec3, PxVec3, PxVec3);
	static PxParticleCreationData createRandomParticleData(int, int, ParticleData*, PxVec3);
	static MeshData* createMeshData(PxParticleSystem*);
};

#endif

#include "ParticleFactory.h"

using namespace physx;


/* creates particle system
 * max = max number of particles
 * physics = particle system is created from PxPhysics object
 * data = particle creation data from calling createParticleData()
 */
PxParticleSystem* ParticleFactory::createParticles(int max, PxPhysics* physics, PxParticleCreationData data) {
	PxParticleSystem* parSystem;

	parSystem = physics->createParticleSystem(max, false);

	bool success = parSystem->createParticles(data);
	if(!success)
		fprintf(stderr, "Couldn't create Particles!\n");

	return parSystem;
}

/* creates creation data for particles
 * max = max particles
 * pData = an empty but initialized instance of ParticleData is preferred
 * last three arguments are constant across particles
 */
PxParticleCreationData ParticleFactory::createParticleData(int max, ParticleData* pData, PxVec3 velocity, PxVec3 position, PxVec3 force) {
	PxParticleCreationData data;

	for(PxU32 i = 0 ; i < (PxU32)max; ++i)
	{
		pData->setIndex(i, i);
		pData->setVelocity(i, velocity);
		pData->setPosition(i, position);
		pData->setForce(i, force);
	}
	data.numParticles = 200;
	data.indexBuffer = PxStrideIterator<const PxU32> (pData->getIndexes());
	data.velocityBuffer = PxStrideIterator<const PxVec3> (pData->getVelocities());
	data.positionBuffer = PxStrideIterator<const PxVec3> (pData->getPositions());

	return data;
}
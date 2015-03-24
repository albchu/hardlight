
#include "ParticleFactory.h"

PxParticleSystem* ParticleFactory::createParticles(int max, PhysxAgent agent, PxParticleCreationData data) {
	PxParticleSystem* parSystem;

	parSystem = agent.get_physics()->createParticleSystem(max, false);

	bool success = parSystem->createParticles(data);
	if(!success)
		fprintf(stderr, "Couldn't create Particles!\n");

	return parSystem;
}

PxParticleCreationData ParticleFactory::createParticleData(int max, ParticleData* pData, vec3 velocity, vec3 position, vec3 force) {
	PxParticleCreationData data;

	for(PxU32 i = 0 ; i < (PxU32)max; ++i)
	{
		pData->setIndex(i, i);
		pData->setVelocity(i, PxVec3(velocity.x, velocity.y, velocity.z));
		pData->setPosition(i, PxVec3(position.x, position.y, position.z));
		pData->setForce(i, PxVec3(force.x, force.y, force.z));
	}
	data.numParticles = 200;
	data.indexBuffer = PxStrideIterator<const PxU32> (pData->getIndexes());
	data.velocityBuffer = PxStrideIterator<const PxVec3> (pData->getVelocities());
	data.positionBuffer = PxStrideIterator<const PxVec3> (pData->getPositions());

	return data;
}
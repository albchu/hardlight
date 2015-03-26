
#include "ParticleFactory.h"
#include <stdlib.h>
#include <time.h>

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
 * num = number of particles, must be less than the maximum number of particles
 * pData = an empty but initialized instance of ParticleData is preferred
 * last three arguments are constant across particles
 */
PxParticleCreationData ParticleFactory::createParticleData(int num, ParticleData* pData, PxVec3 velocity, PxVec3 position, PxVec3 force) {
	PxParticleCreationData data;

	for(PxU32 i = 0 ; i < (PxU32)num; ++i)
	{
		pData->setIndex(i, i);
		pData->setVelocity(i, velocity);
		pData->setPosition(i, position);
		pData->setForce(i, force);
	}
	data.numParticles = num;
	data.indexBuffer = PxStrideIterator<const PxU32> (pData->getIndexes());
	data.velocityBuffer = PxStrideIterator<const PxVec3> (pData->getVelocities());
	data.positionBuffer = PxStrideIterator<const PxVec3> (pData->getPositions());

	return data;
}

/*
 * Provided a location, randomly assigns velocities and forces to all points.
 * For explosions!
 */
PxParticleCreationData ParticleFactory::createRandomParticleData(int num, int maxVelocity, ParticleData* pData, PxVec3 position) {
	PxParticleCreationData data;

	srand(time(NULL));

	for(PxU32 i = 0; i < (PxU32)num; ++i) {
		double rx = rand() % maxVelocity - maxVelocity/2;
		double ry = rand() % maxVelocity - maxVelocity/2;
		double rz = rand() % maxVelocity - maxVelocity/2;

		pData->setIndex(i, i);
		pData->setVelocity(i, PxVec3(rx, ry, rz));
		pData->setPosition(i, position);
		pData->setForce(i, PxVec3(rx, ry, rz));
	}

	data.numParticles = num;
	data.indexBuffer = PxStrideIterator<const PxU32> (pData->getIndexes());
	data.velocityBuffer = PxStrideIterator<const PxVec3> (pData->getVelocities());
	data.positionBuffer = PxStrideIterator<const PxVec3> (pData->getPositions());

	return data;

}

// Gets meshdata version of particlesystem
MeshData* ParticleFactory::createMeshData(PxParticleSystem* system) {
	MeshData* newMesh = new MeshData();

	PxParticleReadData* readParticle = system->lockParticleReadData();
	if(readParticle) {
		PxStrideIterator<const PxParticleFlags> flagIt(readParticle->flagsBuffer);
		PxStrideIterator<const PxVec3> positionIt(readParticle->positionBuffer);

		for(unsigned int j = 0 ; j < readParticle->validParticleRange; ++j, ++flagIt , ++positionIt)
		{
			if(*flagIt & PxParticleFlag::eVALID)
			{
				const PxVec3& pos = *positionIt;
				newMesh->addVertex(vec3(pos.x, pos.y, pos.z));

			}
		}

	}
	readParticle->unlock();

	return newMesh;
}
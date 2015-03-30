#include "ParticleFactory.h"
#include "Common.h"
#include <stdlib.h>
#include <time.h>

using namespace physx;


/* creates particle system
 * max = max number of particles
 * physics = particle system is created from PxPhysics object
 * data = particle creation data from calling createParticleData()
 */
PxParticleSystem* ParticleFactory::createParticles(int max, PxPhysics* physics, PxParticleCreationData data)
{
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
 *//*
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
*/
/*
 * Provided a location, randomly assigns velocities and forces to all points.
 * For explosions!
 */
PxParticleCreationData ParticleFactory::createRandomParticleData(int num, float maxVelocity, ParticleData* pData, PxVec3 position)
{
	PxParticleCreationData data;

	for(PxU32 i = 0; i < (PxU32)num; ++i)
	{
		float rx = Common::getRandFloat(-1.f, 1.f);
		float ry = Common::getRandFloat(0.f, 1.f);
		float rz = Common::getRandFloat(-1.f, 1.f);
		PxVec3 direction = PxVec3(rx, ry, rz).getNormalized();
		direction = direction * maxVelocity;
		pData->setIndex(i, i);
		pData->setVelocity(i, direction);
		pData->setPosition(i, position);
		pData->setForce(i, direction);
	}
	
	data.numParticles = num;
	data.indexBuffer = PxStrideIterator<const PxU32> (pData->getIndexes());
	data.velocityBuffer = PxStrideIterator<const PxVec3> (pData->getVelocities());
	data.positionBuffer = PxStrideIterator<const PxVec3> (pData->getPositions());

	return data;
}

// Gets meshdata version of particlesystem
MeshData* ParticleFactory::createMeshData(PxParticleSystem* system)
{
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
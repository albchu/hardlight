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

	parSystem->setParticleReadDataFlag(PxParticleReadDataFlag::eVELOCITY_BUFFER, true);
	parSystem->setMaxMotionDistance(2.f);
	return parSystem;
}

/*
 * Provided a location, randomly assigns velocities and forces to all points.
 * For explosions!
 */
PxParticleCreationData ParticleFactory::createRandomParticleData(int num, float maxVelocity, ParticleData* pData, PxVec3 position)
{
	PxParticleCreationData data;

	for(PxU32 i = 0; i < (PxU32)num; ++i)
	{
		pData->setIndex(i, i);
		pData->setPosition(i, position);

		float rx = Common::getRandFloat(-1.f, 1.f);
		float ry = Common::getRandFloat(0.f, 1.f);
		float rz = Common::getRandFloat(-1.f, 1.f);
		PxVec3 velocity = PxVec3(rx, ry, rz).getNormalized();
		velocity = velocity * maxVelocity;
		pData->setVelocity(i, velocity);
	}
	data.numParticles = num;
	data.indexBuffer = PxStrideIterator<const PxU32> (pData->getIndexes());
	data.positionBuffer = PxStrideIterator<const PxVec3> (pData->getPositions());
	data.velocityBuffer = PxStrideIterator<const PxVec3> (pData->getVelocities());

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
		PxStrideIterator<const PxVec3> velocityIt(readParticle->velocityBuffer);

		for(unsigned int j = 0 ; j < readParticle->validParticleRange; ++j, ++flagIt , ++positionIt, ++velocityIt)
		{
			if(*flagIt & PxParticleFlag::eVALID)
			{
				const PxVec3& pos = *positionIt;
				const PxVec3& velocity = *velocityIt;
				newMesh->addVertex(vec3(pos.x, pos.y, pos.z));
			}
		}
	}
	readParticle->unlock();

	return newMesh;
}
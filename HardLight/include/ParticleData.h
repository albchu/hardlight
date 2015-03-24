
#ifndef _PARTICLEDATA_H_
#define _PARTICLEDATA_H_

#include <PxPhysicsAPI.h>

class ParticleData {
private:
	int size;
	physx::PxU32* indexes;
	physx::PxVec3* velocities;
	physx::PxVec3* positions;
	physx::PxVec3* forces;
public:
	ParticleData();
	ParticleData(int);

	physx::PxU32* getIndexes();
	void setIndex(int, physx::PxU32);

	physx::PxVec3* getVelocities();
	void setVelocity(int, physx::PxVec3);

	physx::PxVec3* getPositions();
	void setPosition(int, physx::PxVec3);

	physx::PxVec3* getForces();
	void setForce(int, physx::PxVec3);
};

#endif

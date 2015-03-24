
#ifndef _PARTICLEDATA_H_
#define _PARTICLEDATA_H_

#include "HardLight.h"

class ParticleData {
private:
	int size;
	PxU32* indexes;
	PxVec3* velocities;
	PxVec3* positions;
	PxVec3* forces;
public:
	ParticleData();
	ParticleData(int);

	PxU32* getIndexes();
	void setIndex(int, PxU32);

	PxVec3* getVelocities();
	void setVelocity(int, PxVec3);

	PxVec3* getPositions();
	void setPosition(int, PxVec3);

	PxVec3* getForces();
	void setForce(int, PxVec3);
};

#endif

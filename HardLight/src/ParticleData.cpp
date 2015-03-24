
#include "ParticleData.h"

using namespace physx;

ParticleData::ParticleData() {
	size = 0;
	indexes = new PxU32[];
	velocities = new PxVec3[];
	positions = new PxVec3[];
	forces = new PxVec3[];
}

ParticleData::ParticleData(int max) {
	size = max;
	indexes = new PxU32[max];
	velocities = new PxVec3[max];
	positions = new PxVec3[max];
	forces = new PxVec3[max];
}

PxU32* ParticleData::getIndexes() {
	return indexes;
}

void ParticleData::setIndex(int index, PxU32 value) {
	if(index < 0 || index  > size - 1) {
		return;
	}
	indexes[index] = value;
}

PxVec3* ParticleData::getVelocities() {
	return velocities;
}

void ParticleData::setVelocity(int index, PxVec3 velocity) {
	if(index < 0 || index  > size - 1) {
		return;
	}
	velocities[index] = velocity;
}

PxVec3* ParticleData::getPositions() {
	return positions;
}

void ParticleData::setPosition(int index, PxVec3 position) {
	if(index < 0 || index  > size - 1) {
		return;
	}
	positions[index] = position;
}

PxVec3* ParticleData::getForces() {
	return forces;
}

void ParticleData::setForce(int index, PxVec3 force) {
	if(index < 0 || index  > size - 1) {
		return;
	}
	forces[index] = force;
}
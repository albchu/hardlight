#include "PhysxAgent.h"

vec3 Physx_Agent::toVec3(PxVec3 pxvec3)
{
	return vec3(pxvec3.x, pxvec3.y, pxvec3.z);
}
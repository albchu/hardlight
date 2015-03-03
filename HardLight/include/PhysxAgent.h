#ifndef _PHYSX_AGENT_H_
#define _PHYSX_AGENT_H_

#include <glm/glm.hpp>		// Used for vec3
#include <PxPhysicsAPI.h>

using namespace glm;
using namespace physx;

// This class should be the single point of access for all our physx objects and also general useful functions
class Physx_Agent
{
public:
	static vec3 toVec3(PxVec3);
};
#endif
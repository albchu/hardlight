#ifndef _TAIL_SEG_H
#define _TAIL_SEG_H

#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"
#include <PxPhysicsAPI.h>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;
using namespace std;

#pragma once
class TailSegment: public Entity
{
protected:
	float tailScale;
public:
	void CreateTail(vec3 topLeft, vec3 topRight, float height);
	TailSegment();
	~TailSegment();
	
	TailSegment(PxRigidActor* actor, MeshData* meshdata, const char* texture):Entity(actor, meshdata, texture){};
	mat4 get_model_matrix();
	void setScale(float size);
};

#endif
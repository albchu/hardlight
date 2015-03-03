#ifndef _TAIL_SEG_H
#define _TAIL_SEG_H

#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"
#include <PxPhysicsAPI.h>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;
using namespace std;

// This class does not inherit entity but holds an actor because TailWall will need the actors for rendering
class TailSegment//: public Entity
{
private:
	//float tailScale;
	PxActor* actor;
	vec3 start;
	vec3 end;
	float width;	// How wide the segment will be
	float height;	// How high the segment will be


public:
	TailSegment(vec3 new_start, vec3 new_end);
	vector<vec3> get_wall_mesh();
	//void CreateTail(vec3 topLeft, vec3 topRight, float height);
	//TailSegment();
	
	//TailSegment(PxRigidActor* actor, MeshData* meshdata, const char* texture):Entity(actor, meshdata, texture){};
	//mat4 get_model_matrix();
	//void setScale(float size);
};

#endif
#ifndef _TAIL_SEG_H
#define _TAIL_SEG_H

#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"
#include <PxPhysicsAPI.h>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;
using namespace std;

class TailSegment: public Entity
{
private:
	//float tailScale;
	//PxActor* actor;
	vec3 start;
	vec3 end;
	float width;	// How wide the segment will be
	float height;	// How high the segment will be
	vector<vec3> mesh;

public:
	TailSegment(vec3 new_start, vec3 new_end, PxRigidActor* init_actor, GLuint new_texture);
	void generate_wall_mesh();
	//void CreateTail(vec3 topLeft, vec3 topRight, float height);
	//TailSegment();
	virtual mat4 get_model_matrix();
	//TailSegment(PxRigidActor* actor, MeshData* meshdata, const char* texture):Entity(actor, meshdata, texture){};
	//mat4 get_model_matrix();
	//void setScale(float size);
};

#endif
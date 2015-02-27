#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"
#include <PxPhysicsAPI.h>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;
using namespace std;

#pragma once
class TailWall: public Entity
{
protected:
	vector<vec3> Tails;
	vector<vec3> Normals;
	vector<vec2> TailUV;

public:
	void CreateTail(vec3 topLeft, vec3 topRight, float height);
	vector<vec3> getTail(void);
	vector<vec3> getTailNorm(void);
	vector<vec2> getTailUV(void);
	TailWall();
	TailWall(PxRigidActor* actor, MeshData* meshdata, const char* texture):Entity(actor, meshdata, texture){};
	mat4 get_model_matrix();
};


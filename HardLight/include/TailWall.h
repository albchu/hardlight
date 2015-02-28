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
	float tailScale;
public:
	void CreateTail(vec3 topLeft, vec3 topRight, float height);
	TailWall();
	~TailWall();
	
	TailWall(PxRigidActor* actor, MeshData* meshdata, const char* texture):Entity(actor, meshdata, texture){};
	mat4 get_model_matrix();
	void setScale(float size);
};


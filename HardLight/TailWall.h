#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"

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

};


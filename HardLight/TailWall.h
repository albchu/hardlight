#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

#pragma once
class TailWall
{
protected:
	vector<vec3> Tails;

public:
	void CreateTail(vec3 topLeft, vec3 topRight, float height);
	vector<vec3> getTail(void);
};


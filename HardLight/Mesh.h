#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Mesh
{
private:

public:
	static vector<vec3> createPlaneMesh();

};

#endif
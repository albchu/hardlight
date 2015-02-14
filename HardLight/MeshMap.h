#ifndef _MESHMAP_H_
#define _MESHMAP_H_


#include "MeshData.h"
#include "Entity.h"

#include <vector>
#include <map>
#include <string>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class MeshMap
{
private:

	map<string, MeshData> meshes;

public:
	static vector<vec3> createPlaneMesh();

	MeshData getEntityMesh(string);
	void setEntityMesh(string, MeshData);
	void deleteEntityMesh(string);
};

#endif
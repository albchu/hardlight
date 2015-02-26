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
	MeshMap();
	MeshData* getEntityMesh(string);
	void setEntityMesh(string, MeshData);
	void deleteEntityMesh(string);
	void loadAllOBJs(const char*);
};

#endif
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
	MeshMap();  // Private so that it can  not be called
	static MeshMap* m_pInstance;
	map<string, MeshData> meshes;

public:
	static MeshMap* Instance();		// Singleton pattern
	
	MeshData* getEntityMesh(string);
	void setEntityMesh(string, MeshData);
	void deleteEntityMesh(string);
	void loadAllOBJs(const char*);
};

#endif
#include "MeshMap.h"
#include "tempOBJ\objloader.hpp"

MeshMap::MeshMap()
{
	setEntityMesh("HardLightBike", loadOBJ("../data/HardlightBike.obj"));
	setEntityMesh("plane", loadOBJ("../data/plane.obj"));
}

MeshData* MeshMap::getEntityMesh(string ent)
{
	return &meshes[ent]; 
}

void MeshMap::setEntityMesh(string ent, MeshData m_data)
{
	meshes[ent] = m_data;
}

void MeshMap::deleteEntityMesh(string ent)
{
	meshes.erase(ent);
}
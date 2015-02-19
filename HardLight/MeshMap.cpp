#include "MeshMap.h"
#include "tempOBJ\objloader.hpp"

MeshMap::MeshMap()
{
	MeshData bike;
	loadOBJ("../data/HardLightBike.obj", bike.m_vertices, bike.m_textures, bike.m_normals);
	meshes["HardLightBike"] = bike;
	MeshData plane;
	loadOBJ("../data/plane.obj", plane.m_vertices, plane.m_textures, plane.m_normals);
	meshes["plane"] = plane;
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
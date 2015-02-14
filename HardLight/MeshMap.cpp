#include "MeshMap.h"

vector<vec3> MeshMap::createPlaneMesh()
{
	vector<vec3> mesh;

	mesh.push_back(vec3(-25.0f, 25.0f, -100.0f));
	mesh.push_back(vec3(-25.0f, -57.0f, 0.0f));
	mesh.push_back(vec3(405.0f, 25.0f, 0.0f));
	mesh.push_back(vec3(25.0f, -25.0f, 0.0f));

	return mesh;
}

MeshData MeshMap::getEntityMesh(string ent)
{
	return meshes[ent]; 
}

void MeshMap::setEntityMesh(string ent, MeshData m_data)
{
	meshes[ent] = m_data;
}

void Mesh::deleteEntityMesh(string ent)
{
	meshes.erase(ent);
}
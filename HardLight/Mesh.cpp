#include "Mesh.h"

vector<vec3> Mesh::createPlaneMesh()
{
	vector<vec3> mesh;

	mesh.push_back(vec3(-25.0f, 25.0f, -100.0f));
	mesh.push_back(vec3(-25.0f, -57.0f, 0.0f));
	mesh.push_back(vec3(405.0f, 25.0f, 0.0f));
	mesh.push_back(vec3(25.0f, -25.0f, 0.0f));

	return mesh;
}

MeshData Mesh::getEntityMesh(string ent)
{
	return meshes[ent]; 
}

void Mesh::setEntityMesh(string ent, MeshData m_data)
{
	meshes[ent] = m_data;
}

void Mesh::deleteEntityMesh(string ent)
{
	meshes.erase(ent);
}
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
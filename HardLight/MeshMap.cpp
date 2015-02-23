#include "MeshMap.h"
#include "tempOBJ\objloader.hpp"
#include "objParser.h"
#include "ParsedFile.h"

MeshMap::MeshMap()
{
	
	objParser parser;

	MeshData bike = parser.loadObj(ParsedFile("../data/HardlightBike.obj"));
	MeshData plane = parser.loadObj(ParsedFile("../data/plane.obj"));

	bike.order_Arrays();
	plane.order_Arrays();

	setEntityMesh("HardLightBike", bike);
	setEntityMesh("plane", plane);

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
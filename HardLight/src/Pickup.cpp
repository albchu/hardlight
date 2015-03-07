#include "Pickup.h"

Pickup::Pickup()
{
	type = PICKUP;
	draw_mode = GL_TRIANGLES;
	mesh_data = MeshMap::Instance()->getEntityMesh("HardLightPickup.obj");
	deleted = false;

	world = NULL;
	pickup = NULL;
	maxPickups = 0;
	heightOffFloor = 0.0f;
}

Pickup::Pickup(World* world, Pickup* pickup, INIReader* config)
{
	this->world = world;
	this->pickup = pickup;
	maxPickups = config->GetInteger("pickup", "maxPickups", 1);
	heightOffFloor = config->GetReal("pickup", "heightOffFloor", 5.0f);

	glm::vec3 point;
	glm::vec3 normal;
	MeshData* meshdata;
	vector<Entity*> entities = world->getEntities();
	int pointIndex;

	// Find floor entity, get mesh data
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i]->get_type() == FLOOR)
		{
			meshdata = entities[i]->get_mesh_data();
		}

		pointIndex = rand() % meshdata->getVertices()->size(); // Pick a random index, which points to a vertex in m_vertices
	}
	point = meshdata->getVertex(pointIndex); // get the randomly selected vertex
	normal = meshdata->getNormal(pointIndex); // get the normal that corresponds to the randomly seleced vertex


	point = heightOffFloor*normal + point; // vector equation of a line (Line-plane intersection)
	
	// Generate powerup with random powerup type

	// Create physx actor and model centered at 'point'
}


Pickup::~Pickup(){}

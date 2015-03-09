#include "Pickup.h"

Pickup::Pickup()
{
	type = PICKUP;
	draw_mode = GL_TRIANGLES;
	mesh_data = MeshMap::Instance()->getEntityMesh("tail.obj");
	renderable = true;
	texture = TextureMap::Instance()->getTexture("../data/Textures/MoonSkybox.tga");


	world = NULL;
	maxPickups = 0;
	heightOffFloor = 0.0f;
}

Pickup::Pickup(World* world, INIReader* config, PhysxAgent* pxAgent)
{
	type = PICKUP;
	draw_mode = GL_TRIANGLES;
	mesh_data = MeshMap::Instance()->getEntityMesh("tail.obj");
	renderable = true;
	texture = TextureMap::Instance()->getTexture("../data/Textures/MoonSkybox.tga");

	this->world = world;
	maxPickups = config->GetInteger("pickup", "maxPickups", 1);
	heightOffFloor = (float)config->GetReal("pickup", "heightOffFloor", 5.0f);

	glm::vec3 point;
	glm::vec3 normal;
	vector<Entity*> entities = world->getEntities();
	int pointIndex;

	// Find floor entity, get mesh data
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i]->get_type() == FLOOR)
		{
			mesh_data = entities[i]->get_mesh_data();
		}

		pointIndex = rand() % mesh_data->getVertices()->size(); // Pick a random index, which points to a vertex in m_vertices
	}
	point = mesh_data->getVertex(pointIndex); // get the randomly selected vertex
	normal = mesh_data->getNormal(pointIndex); // get the normal that corresponds to the randomly seleced vertex


	point = heightOffFloor*normal + point; // vector equation of a line (Line-plane intersection)
	
	// Generate powerup with random powerup type

	// Create physx actor and model centered at 'point'
	actor = pxAgent->create_pickup(vec3(0.0,0.0,0.0), vec3(0.0,1.0,0.0));
}


Pickup::~Pickup(){}

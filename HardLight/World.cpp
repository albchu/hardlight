#include "World.h"

// Creates an entity with a PxActor and adds it to the list of entities
void World::add_entity(PxActor* init_actor)
{
	vector<vec3> empty_mesh;
	add_entity(init_actor, empty_mesh);
}

void World::add_entity(PxActor* init_actor, vector<vec3>& init_mesh)
{
	Entity entity = Entity(init_actor, init_mesh);
	add_entity(entity);
}

void World::add_entity(Entity& entity)
{
	entities.push_back(entity);
}

vector<Entity> World::getEntities()
{
	return entities;
}
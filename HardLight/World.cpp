#include "World.h"

// Creates an entity with a PxActor and adds it to the list of entities
void World::add_entity(PxActor& actor)
{
	Entity entity;
	entity.set_actor(actor);
	entities.push_back(entity);
}

vector<Entity> World::getEntities()
{
	return entities;
}
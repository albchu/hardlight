#include "World.h"

// Creates an entity with a PxActor and adds it to the list of entities
Entity World::add_entity(PxActor& actor)
{
	Entity entity;
	entity.set_actor(actor);
	entities.push_back(entity);
	return entity;
}

Entity World::add_entity(PxActor& actor, vector<vec3> mesh)
{
	Entity entity = add_entity(actor);
	entity.set_mesh(mesh);
	return entity;
}

Entity World::add_entity(Entity& entity)
{
	entities.push_back(entity);
	return entity;
}

vector<Entity> World::getEntities()
{
	return entities;
}
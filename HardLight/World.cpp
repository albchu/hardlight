#include "World.h"

void World::add_entity(Entity* entity)
{
	entities.push_back(entity);
}

vector<Entity*> World::getEntities()
{
	return entities;
}

void World::clear()
{
	for(Entity* e : entities) {
		delete e;
	}

	entities.clear();
}
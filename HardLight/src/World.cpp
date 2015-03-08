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

void World::remove(Entity* entity)
{
	for(unsigned int i = 0; i < entities.size(); i++){
		if(entities[i] == entity){
			entities.erase(entities.begin()+i);
			entity->release();
			delete entity;
			break;
		}
	}
}
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
		free(e);
	}

	entities.clear();
}

void World::remove(Entity* entity)
{
	for(int i = 0; i < entities.size();i++){
		if(entities[i] == entity){
			entities.erase(entities.begin()+i);
			free(entity);
			break;
		}
	}
}
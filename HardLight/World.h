#ifndef _WORLD_H_
#define _WORLD_H_

// This class is the entire world representation. It holds a list of entities with operations on the entities
#include "Entity.h"
#include <vector>
#include "Bike.h"
class World
{
private:
	vector<Entity*> entities;

public:
	void add_entity(Entity* entity);
	void add_bike(PxActor* actor);
	vector<Entity*> getEntities();
};

#endif
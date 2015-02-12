// This class is the entire world representation. It holds a list of entities with operations on the entities
#include "Entity.h"
#include <vector>

class World
{
private:
	vector<Entity> entities;

public:
	//void add_new_actor
	Entity add_entity(PxActor&);
	Entity add_entity(PxActor&, vector<vec3>);
	Entity add_entity(Entity& entity);
	vector<Entity> getEntities();
};
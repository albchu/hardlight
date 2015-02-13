// This class is the entire world representation. It holds a list of entities with operations on the entities
#include "Entity.h"
#include <vector>

class World
{
private:
	vector<Entity> entities;

public:
	//void add_new_actor
	void add_entity(PxActor* init_actor);
	void add_entity(PxActor* init_actor, vector<vec3>& init_mesh);
	void add_entity(Entity& entity);
	vector<Entity> getEntities();
};
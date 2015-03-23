#ifndef _WALL_H_
#define _WALL_H_

/*
 * Represents arena walls
 *
 * overloads model matrix
 */

#include "Entity.h"

class Wall : public Entity {
public:
	Wall(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint new_texture, vec3 init_scale);
};

#endif
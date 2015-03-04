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
	Wall();
	Wall(PxRigidActor* init_actor, MeshData* init_mesh_data, const char* texture_file_path);
	~Wall();
	virtual mat4 get_model_matrix();
};

#endif
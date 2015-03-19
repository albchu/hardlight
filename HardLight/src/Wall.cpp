
#include "Wall.h"
#include <glm/glm.hpp>
#include <glm\gtx\rotate_vector.hpp>

Wall::Wall(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint new_texture, vec3 init_scale)
{
	type = WALL;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = new_texture;
	init_opengl();
	renderable = true;
	scale_factor = vec3(init_scale.x, 20.f, init_scale.z);
}

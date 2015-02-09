#include "Entity.h"

Entity::Entity(vec3 init_position, vector<vec3> init_mesh)
{
	position = init_position;
	mesh = init_mesh;
}

Entity::Entity()
{
}

// Renders an object to opengl
void Entity::render()
{

}

vector<vec3> Entity::get_mesh()
{
	return mesh;
}

void Entity::set_mesh(vector<vec3> new_mesh)
{
	mesh = new_mesh;
}

void Entity::set_position(vec3 new_position)
{
	position = new_position;
}

vec3 Entity::get_position()
{
	return position;
}

void Entity::set_model(mat4 new_model)
{
	model = new_model;
}

mat4 Entity::get_model()
{
	return model;
}

void Entity::set_vao(GLuint new_vao)
{
	vao = new_vao;
}

GLuint Entity::get_vao()
{
	return vao;
}

void Entity::set_vbo(GLuint new_vbo)
{
	vbo = new_vbo;
}

GLuint Entity::get_vbo()
{
	return vbo;
}

void Entity::set_cbo(GLuint new_cbo)
{
	cbo = new_cbo;
}

GLuint Entity::get_cbo()
{
	return cbo;
}

void Entity::set_actor(PxActor* new_actor)
{
	actor = new_actor;
}

PxActor* Entity::get_actor()
{
	return actor;
}

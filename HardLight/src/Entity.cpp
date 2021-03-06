#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint new_texture, vec3 init_scale)
{
	type = UNDECLARED;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = new_texture;
	init_opengl();
	renderable = true;
	scale_factor = init_scale;
}

Entity::Entity()
{
	type = UNDECLARED;
	draw_mode = GL_TRIANGLES;
	//mesh_data = new MeshData();
	renderable = true;
}

Entity::~Entity()
{
	glDeleteBuffers(1, &normal_buffer_id);
	glDeleteBuffers(1, &texture_buffer_id);
	glDeleteBuffers(1, &vertex_buffer_id);
	glDeleteVertexArrays(1, &vertex_array_id);
}

void Entity::init_opengl()
{
	// Create and compile our GLSL program from the shaders
	program_id = LoadShaders("basic_vs.glsl", "basic_fs.glsl");
	init_opengl(program_id);
}

// Holds all the preamble required to render a proper opengl object later on
void Entity::init_opengl(GLuint init_program_id)
{
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	program_id = init_program_id;

	// Get a handle for our "MVP" uniform
	mvp_matrix_id = glGetUniformLocation(program_id, "MVP");
	view_matrix_id = glGetUniformLocation(program_id, "V");
	model_matrix_id = glGetUniformLocation(program_id, "M");

	// Get a handle for our "myTextureSampler" uniform
	texture_id  = glGetUniformLocation(program_id, "myTextureSampler");

	// Load OBJ into a VBO
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER,
		mesh_data->getVertices()->size() * sizeof(vec3),
		&mesh_data->getVertices()->at(0),
		GL_STATIC_DRAW);

	glGenBuffers(1, &texture_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_id);
	glBufferData(GL_ARRAY_BUFFER,
		mesh_data->getTextureCoordinates()->size() * sizeof(vec2),
		&mesh_data->getTextureCoordinates()->at(0),
		GL_STATIC_DRAW);

	glGenBuffers(1, &normal_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_id);
	glBufferData(GL_ARRAY_BUFFER,
		mesh_data->getNormals()->size() * sizeof(vec3),
		&mesh_data->getNormals()->at(0),
		GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(program_id);
	light_id = glGetUniformLocation(program_id, "LightPosition_worldspace");
}

mat4 Entity::get_model_matrix()
{
	PxTransform gPose = actor->getGlobalPose();
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);

	mat4 t_matrix = glm::translate(vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	mat4 r_matrix = glm::rotate(rads, vec3(axis.x, axis.y, axis.z));
	mat4 s_matrix = glm::scale(scale_factor);

	return t_matrix * r_matrix * s_matrix;
}

void Entity::render(mat4 projection_matrix, mat4 view_matrix, vec3 light)
{
	// Use our shader
	glUseProgram(program_id);

	mat4 model_matrix = this->get_model_matrix();

	mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(mvp_matrix_id, 1, GL_FALSE, &mvp_matrix[0][0]);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &model_matrix[0][0]);
	glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &view_matrix[0][0]);

	glUniform3f(light_id, light.x, light.y, light.z);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(texture_id, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer_id);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_id);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(draw_mode, 0, mesh_data->getVertices()->size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Entity::set_mesh_data(MeshData* new_mesh_data)	{ mesh_data = new_mesh_data; }
MeshData*	Entity::get_mesh_data()					{ return mesh_data; }

void Entity::set_draw_mode(GLuint& new_draw_mode)	{ draw_mode = new_draw_mode; }
GLuint Entity::get_draw_mode()						{ return draw_mode; }

void Entity::set_actor(PxRigidActor* new_actor)		{ actor = new_actor; }
PxRigidActor* Entity::get_actor()					{ return actor; }
int Entity::get_type()								{ return type; }
void Entity::set_type(EntityTypes type)				{ this->type = type; }

void Entity::set_texture(GLuint new_texture)		{ texture = new_texture; }

void Entity::release(){
	actor->release();
}

void Entity::set_renderable(bool flag)
{
	renderable = flag;
}

void Entity::toggle_renderable()
{
	renderable = !renderable;
}

bool Entity::is_renderable()
{
	return renderable;
}

vec3 Entity::get_location()
{
	PxTransform gPose = actor->getGlobalPose();
	return vec3(gPose.p.x, gPose.p.y, gPose.p.z);
}

vec3 Entity::get_direction_vector()
{
	PxQuat q = actor->getGlobalPose().q;
	PxVec3 global_forward = PxVec3(0,0,1);

	return normalize(PhysxAgent::toVec3(q.rotate(global_forward)));
}

// base off gravity
vec3 Entity::get_up_vector()
{
	PxTransform gPose = actor->getGlobalPose();
	PxQuat q = gPose.q;
	PxVec3 global_up = PxVec3(0.0f,1.0f,0.0f);

	return normalize(PhysxAgent::toVec3(global_up));
}

float Entity::get_distance(Entity* other)
{
	return (this->actor->getGlobalPose().p - other->actor->getGlobalPose().p).magnitude();
}

GLuint Entity::get_texture()
{
	return texture;
}


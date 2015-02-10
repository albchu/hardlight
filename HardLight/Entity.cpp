#include "Entity.h"

Entity::Entity(vec3 init_position, vector<vec3> init_mesh)
{
	position = init_position;
	mesh = init_mesh;
	Entity();
}

Entity::Entity()
{
	initVAO();
	initVBO();
	initCBO();
	setupVAO();
	setupVBO();
	setupCBO();
}

void Entity::initVAO() {
	glGenVertexArrays(1, &vao);
}

void Entity::initVBO() {
	glGenBuffers(1, &vbo);
}

void Entity::initCBO() {
	glGenBuffers(1, &cbo);
}

void Entity::setupVAO() {
	glBindVertexArray(vao);
}

void Entity::setupVBO() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}

void Entity::setupCBO() {
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}

string loadShader(string filePath) {
	string shaderCode;
	ifstream fileStream( filePath.c_str(), std::ios::in );
	if( fileStream.is_open() )
	{
		std::string line;
		while( getline( fileStream, line ) )
		{
			shaderCode += "\n" + line;
		}
		fileStream.close();
	
	}
	else
	{
		cerr << "Could Not Open File " << filePath << std::endl;
	}
	return shaderCode;	
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

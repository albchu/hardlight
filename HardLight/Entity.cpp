#include "Entity.h"

Entity::Entity(PxActor* init_actor, vector<vec3>& init_mesh)
{
	draw_mode = GL_TRIANGLE_STRIP;
	actor = init_actor;
	mesh = init_mesh;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	programID = LoadShaders("StandardShading.vertexshader", "basic_fs.glsl");
}

void Entity::initProgramID() {
	std::string vsSource = loadShaderStringfromFile("./basic_vs.glsl");
	std::string fsSource = loadShaderStringfromFile("./basic_fs.glsl");
	program_id = CreateShaderProgram(vsSource, fsSource);
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
}

void Entity::setupCBO() {
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
}

void Entity::render()
{
	glUseProgram(program_id);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.size()*3);

}

vector<vec3> Entity::get_mesh()
{
	return mesh;
}

void Entity::set_mesh(vector<vec3>& new_mesh)
{
	mesh = new_mesh;
}

void Entity::set_vao(GLuint& new_vao)
{
	vao = new_vao;
}

GLuint Entity::get_vao()
{
	return vao;
}

void Entity::set_vbo(GLuint& new_vbo)
{
	vbo = new_vbo;
}

GLuint Entity::get_vbo()
{
	return vbo;
}

void Entity::set_cbo(GLuint& new_cbo)
{
	cbo = new_cbo;
}

GLuint Entity::get_cbo()
{
	return cbo;
}

void Entity::set_program_id(GLuint& new_program_id)
{
	program_id = new_program_id;
}

GLuint Entity::get_program_id()
{
	return program_id;
}

void Entity::set_draw_mode(GLuint& new_draw_mode)
{
	draw_mode = new_draw_mode;
}

GLuint Entity::get_draw_mode()
{
	return draw_mode;
}

void Entity::set_actor(PxActor* new_actor)
{
	actor = new_actor;
}

PxActor* Entity::get_actor()
{
	return actor;
}

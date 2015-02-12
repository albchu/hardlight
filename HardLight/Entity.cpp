#include "Entity.h"

Entity::Entity(vec3 init_position, vector<vec3> init_mesh)
{
	position = init_position;
	mesh = init_mesh;
	Entity();
}

Entity::Entity()
{
	initProgramID();
	initVAO();
	initVBO();
	initCBO();
	setupVAO();
	setupVBO();
	setupCBO();
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



////#############################################################################
////  load a shader file into opengl
////  This code is from the openGL tutorial:
////  http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
////#############################################################################
//void Entity::createShaderProgram(string vertex_shader_path, string fragment_shader_path) {
//
//	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
//	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//	
//	string Line;
//	
//	string VertexShaderCode;
//	ifstream VertexShaderStream(vertex_shader_path, ios::in);
//	if(VertexShaderStream.is_open()) {
//		Line = "";
//		while(getline(VertexShaderStream, Line))
//			VertexShaderCode += "\n" + Line;
//		VertexShaderStream.close();
//	}
//	
//	string FragmentShaderCode;
//	ifstream FragmentShaderStream(fragment_shader_path, ios::in);
//	if(FragmentShaderStream.is_open()) {
//		Line = "";
//		while(getline(FragmentShaderStream, Line))
//			FragmentShaderCode += "\n" + Line;
//		FragmentShaderStream.close();
//	}
//	
//	GLint Result = GL_FALSE;
//	int InfoLogLength;
//	
//	// Compile Vertex Shader
//	printf("Compiling shader : %s\n", vertex_shader_path);
//	char const * VertexSourcePointer = VertexShaderCode.c_str();
//	glShaderSource(vertexShaderID, 1, &VertexSourcePointer, NULL);
//	glCompileShader(vertexShaderID);
//	
//	// Check Vertex Shader
//	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	vector<char> VertexShaderErrorMessage(InfoLogLength);
//	glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, NULL);
//	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
//	
//	// Compile Fragment Shader
//	printf("Compiling shader : %s\n", fragment_shader_path);
//	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
//	glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer, NULL);
//	glCompileShader(fragmentShaderID);
//	
//	// Check Fragment Shader
//	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
//	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	vector<char> FragmentShaderErrorMessage(InfoLogLength);
//	glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, NULL);
//	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
//	
//	// link program
//	fprintf(stdout, "Linking program\n");
//	GLuint ProgramID = glCreateProgram();
//	glAttachShader(ProgramID, vertexShaderID);
//	glAttachShader(ProgramID, fragmentShaderID);
//	glLinkProgram(ProgramID);
//	
//	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
//	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//	vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
//	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
//	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
//	
//	glDeleteShader(vertexShaderID);
//	glDeleteShader(fragmentShaderID);
//	
//	program_id = ProgramID;
//}

// Renders an object to opengl
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

void Entity::set_position(vec3& new_position)
{
	position = new_position;
}

vec3 Entity::get_position()
{
	return position;
}

void Entity::set_model(mat4& new_model)
{
	model = new_model;
}

mat4 Entity::get_model()
{
	return model;
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

void Entity::set_actor(PxActor& new_actor)
{
	actor = &new_actor;
}

PxActor* Entity::get_actor()
{
	return actor;
}

#ifndef _ENTITY_H_
#define _ENTITY_H_

// The class holds information for each entity in our opengl scene
#include <algorithm>
#include <stdio.h>
#include <string>
#include <fstream>
#include <glm/glm.hpp>		// Used for vec3
#include <vector>
#include <GL/glew.h>
#include <PxPhysicsAPI.h>
#include "ShaderTools.h"

using namespace glm;
using namespace std;
using namespace physx;

#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PxTaskDEBUG.lib")
#pragma comment(lib, "PhysX3VehicleDEBUG.lib")

class Entity
{
private:
	vector<vec3> mesh;		// The manifestation of this entity
	GLuint draw_mode;
	GLuint program_id;
	GLuint vao; // vertex array object
	GLuint vbo; // vertex buffer object
	GLuint cbo; // color buffer object
	PxActor* actor;

public:
	Entity(PxActor*, vector<vec3>&);

	// Buffer object initialization
	void initProgramID();
	void initVAO();
	void initVBO();
	void initCBO();

	void setupVAO();
	void setupVBO();
	void setupCBO();

	// sets program_id
	//void createShaderProgram(string, string);

	void render();
	
	void			set_program_id(GLuint&);
	GLuint			get_program_id();

	// Vertex array object
	void			set_vao(GLuint&);
	GLuint			get_vao();

	// Vertex buffer object
	void			set_vbo(GLuint&);
	GLuint			get_vbo();

	// Color buffer object
	void			set_cbo(GLuint&);
	GLuint			get_cbo();

	void			set_mesh(vector<vec3>&);
	vector<vec3>	get_mesh();

	void			set_actor(PxActor*);
	PxActor*		get_actor();
	
	void			set_draw_mode(GLuint&);
	GLuint			get_draw_mode();
};
#endif

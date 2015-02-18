#ifndef _ENTITY_H_
#define _ENTITY_H_

// The class holds information for each entity in our opengl scene
#include <glm/glm.hpp>		// Used for vec3
#include <vector>
#include <GL/glew.h>
#include <PxPhysicsAPI.h>

#include "ShaderTools.h"
#include "MeshData.h"

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
	GLuint draw_mode;
	MeshData mesh_data;
	GLuint programID;
	GLuint VertexArrayID; // vertex array object
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint TextureID;
	GLuint VertexBufferID; // vertex buffer object
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

	GLuint			getVertexArrayID();
	GLuint			get_vbo();
	void			set_mesh(vector<vec3>&);
	vector<vec3>	get_mesh();

	void			set_actor(PxActor*);
	PxActor*		get_actor();
	
	void			set_draw_mode(GLuint&);
	GLuint			get_draw_mode();
};
#endif

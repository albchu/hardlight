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
	MeshData* mesh_data;
	PxRigidActor* actor;
	GLuint texture;

	GLuint program_id;
	GLuint vertex_array_id;
	GLuint mvp_matrix_id;
	GLuint view_matrix_id;
	GLuint model_matrix_id;
	GLuint texture_id;
	GLuint vertex_buffer_id;
	GLuint normal_buffer_id;
	GLuint texture_buffer_id;
	GLuint light_id;

public:
	Entity(PxRigidActor*, MeshData*, const char*);

	void			render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);

	void			set_texture();

	void			set_mesh_data(MeshData*);
	MeshData*		get_mesh_data();

	void			set_actor(PxRigidActor*);
	PxActor*		get_actor();
	
	void			set_draw_mode(GLuint&);
	GLuint			get_draw_mode();
};
#endif

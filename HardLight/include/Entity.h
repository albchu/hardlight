#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <iostream>
// The class holds information for each entity in our opengl scene
#include <glm/glm.hpp>		// Used for vec3
#include "glm/gtx/string_cast.hpp"		// Used for to_string
#include <vector>
#include <GL/glew.h>
#include <PxPhysicsAPI.h>
#include <cmath>

#include "ShaderTools.h"
#include "MeshData.h"
#include "EntityTypes.h"
#include "MeshMap.h"
#include "PhysxAgent.h"

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
protected:
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
	int type;
	bool deleted;

public:
	Entity(PxRigidActor*, MeshData*, GLuint);
	Entity();
	virtual ~Entity();

	virtual void	render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);

	void			set_texture_path(const char*);

	void			set_mesh_data(MeshData*);
	MeshData*		get_mesh_data();

	virtual void	set_actor(PxRigidActor*);
	PxRigidActor*	get_actor();
	
	void			set_draw_mode(GLuint&);
	GLuint			get_draw_mode();

	// Does all required calculations on a model matrix based
	virtual mat4	get_model_matrix();
	void			init_opengl();
	void			init_opengl(GLuint init_program_id);

	void			set_texture(GLuint);
	
	int				get_type();
	void			set_type(EntityTypes type);
	void			release();

	bool			is_deleted();
	void			set_deleted(bool flag);

	vec3			get_location();
	vec3			get_direction_vector();
	vec3			get_up_vector();
	float			get_distance(Entity* other);
};
#endif

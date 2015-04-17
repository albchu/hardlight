#ifndef _TAIL_SEG_H
#define _TAIL_SEG_H

#include <glm/glm.hpp>
#include <vector>
#include "Entity.h"
#include <PxPhysicsAPI.h>
#include <glm\gtx\rotate_vector.hpp>
#include "Rendering/TextureMap.h"

using namespace glm;
using namespace std;

class TailSegment: public Entity
{
private:
	float width;	// How wide the segment will be
	float height;	// How high the segment will be
	float length;

public:
	TailSegment(PxRigidActor* init_actor, GLuint new_texture, float init_width, float init_height, float init_length, GLuint init_program_id);
	void generate_wall_mesh();
	virtual mat4 get_model_matrix();
};

#endif
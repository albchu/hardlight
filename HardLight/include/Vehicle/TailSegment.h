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
	//float tailScale;
	//PxActor* actor;
	vec3 start;
	vec3 end;
	float width;	// How wide the segment will be
	float height;	// How high the segment will be
	vector<vec3> mesh;

public:
	TailSegment(vec3 new_start, vec3 new_end, PxRigidActor* init_actor, const char * texturePath, INIReader* config);
	void generate_wall_mesh();
	virtual mat4 get_model_matrix();

	void set_start(vec3 new_start);
	void set_end(vec3 new_end);
	vec3 get_start();
	vec3 get_end();
};

#endif
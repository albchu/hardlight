#ifndef _TAIL_WALL_H
#define _TAIL_WALL_H

#include "Entity.h"
#include "Vehicle/TailSegment.h"
#include "vector"

class TailWall : public Entity
{
private:
	vector<TailSegment*> bikeWall;
	int max_length;		// This value will hold exactly how many tail segments will be allowed 

	vector<TailSegment*> segments;
	vec3 last_position;	//The previous start of a tailsegment

public:
	TailWall(vec3);
	//TailSegment* addSegment(TailSegment*);

	// This call will maintain the tail segments 
	void update(vec3 new_location);

	// Needs to be overwritten so we can render the segments correctly
	//virtual void render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);
};

#endif
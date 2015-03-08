#ifndef _TAIL_WALL_H
#define _TAIL_WALL_H

#include "Entity.h"
#include "Vehicle/Bike.h"
#include "Vehicle/TailSegment.h"
#include <vector>

#include "PhysxAgent.h"

class TailWall : public Entity
{
private:
	//vector<TailSegment*> bikeWall;
	unsigned int max_length;		// This value will hold exactly how many tail segments will be allowed 
	vector<TailSegment*> segments;
	vec3 last_position;	//The previous start of a tailsegment
	float min_segment_allowance;	// This variable determines how far a bike must move before we should create a new wall segment
	float max_segment_allowance;	// This variable determines how far a bike must move before we should create a new wall segment
	Bike* bike;		// Reference to its bike
	PxTransform gPose;
	float tail_offset_scalar;
	INIReader* config;

public:
	TailWall(Bike*, INIReader*);

	// This call will maintain the tail segments 
	void update(Physx_Agent*);

	// Needs to be overwritten so we can render the segments correctly
	virtual void render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);
	PxTransform getTailTransform();
	vec3 getTailPosition();
	Bike* getBike();
	void extend_max_length();
};

#endif
#ifndef _TAIL_WALL_H
#define _TAIL_WALL_H

#include "Entity.h"
#include "Vehicle/Chassis.h"
#include "Vehicle/TailSegment.h"
#include <vector>

#include "PhysxAgent.h"

class TailWall : public Entity
{
private:
	unsigned int max_length;		// This value will hold exactly how many tail segments will be allowed 
	unsigned int extend_length;		// This value will hold exactly how many segments will be added when pickup is acquired
	vector<TailSegment*> segments;
	vec3 last_position;	//The previous start of a tailsegment
	float min_segment_allowance;	// This variable determines how far a bike must move before we should create a new wall segment
	float max_segment_allowance;	// This variable determines how far a bike must move before we should create a new wall segment
	Chassis* bike;		// Reference to its bike
	PxTransform gPose;
	float tail_offset_scalar;
	INIReader* config;
	float width;
	float height;

public:
	TailWall(Chassis*, INIReader*);

	// This call will maintain the tail segments 
	void update(PhysxAgent*);

	// Needs to be overwritten so we can render the segments correctly
	virtual void render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos);
	vec3 getTailPosition();
	Chassis* getBike();
	void extend_max_length();
	void set_max_length(int new_length);
	void set_width(float new_width);
	void set_height(float new_height);
};

#endif
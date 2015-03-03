#include "Vehicle/TailWall.h"


TailWall::TailWall(vec3 new_last_position)
{
	max_length = 30;
	last_position = new_last_position;
}

void TailWall::update(vec3 new_position)
{
	// Check the size of the tail list whether to add a new segment or reshuffle segments
	if(segments.size() >= max_length)
	{
		// Reshuffle segments
		//MAGICAL CODE
	}
	else
	{
		// Add new segment to tail
		TailSegment* segment = new TailSegment(new_position, last_position);
		segments.insert(segments.begin(), segment);
	}
}

void TailWall::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	cout << "TAILWALL RENDER!" << endl;
}

//
//TailSegment* TailWall::addSegment(TailSegment* tail){
//	bikeWall.insert(bikeWall.begin(),tail);
//	if(bikeWall.size() > max_length){
//		tail = bikeWall.back();
//		bikeWall.pop_back();
//		return tail;
//	}
//	return NULL;
//}
#include "TailWall.h"


TailWall::TailWall(void)
{
	TailLength = 30;
}


TailWall::~TailWall(void)
{
}

TailSegment* TailWall::addSegment(TailSegment* tail){
	bikeWall.insert(bikeWall.begin(),tail);
	if(bikeWall.size() > TailLength){
		tail = bikeWall.back();
		bikeWall.pop_back();
		return tail;
	}
	return NULL;
}
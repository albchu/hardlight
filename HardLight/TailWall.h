#include "TailSegment.h"
#pragma once
class TailWall
{
private:
	vector<TailSegment*> bikeWall;
	int TailLength;
public:
	TailWall(void);
	~TailWall(void);
	TailSegment* addSegment(TailSegment*);
};


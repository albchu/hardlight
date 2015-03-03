#ifndef _TAIL_WALL_H
#define _TAIL_WALL_H

#include "Vehicle/TailSegment.h"

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

#endif
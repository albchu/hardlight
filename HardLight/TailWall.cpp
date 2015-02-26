#include "TailWall.h"


void TailWall::CreateTail(vec3 topLeft, vec3 topRight, float height)
{
	Tails.push_back(topLeft);
	Tails.push_back(vec3(topLeft.x,topLeft.y-height,topLeft.z));
	Tails.push_back(topRight);
	Tails.push_back(vec3(topLeft.x,topLeft.y-height,topLeft.z));
	Tails.push_back(topRight);
	Tails.push_back(vec3(topRight.x,topRight.y-height,topRight.z));
}


vector<vec3> TailWall::getTail(void)
{
	return Tails;
}

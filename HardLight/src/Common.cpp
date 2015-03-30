#include "Common.h"

float Common::FORTY_FIVE_DEGREES_RADS = 0.785398163f;

float Common::getRandFloat(float low, float high)
{
	float random = rand() / (float)RAND_MAX; // 0 to 1
	float diff = high - low;
	return diff * random + low;
}

int Common::getRandInt(int low, int high)
{
	float random = rand() / (float)RAND_MAX; // 0 to 1
	int diff = high - low;
	return (int)((float)diff * random) + low;
}

int Common::getRandSign()
{
	int random = rand() % 2;
	if (random == 0)
		random = -1;
	return random;
}
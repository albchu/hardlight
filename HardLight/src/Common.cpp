#include "Common.h"

float Common::FORTY_FIVE_DEGREES_RADS = 0.785398163f;

float Common::getRandFloat(float low, float high)
{
	return (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low))));
}

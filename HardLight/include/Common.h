#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

// This class holds the bits and bobs that are useful in alot of places but have no place anywhere
class Common
{
public:
	static float getRandFloat(float low, float high);
	static int getRandInt(int low, int high);
	static float Common::FORTY_FIVE_DEGREES_RADS;
};
#endif
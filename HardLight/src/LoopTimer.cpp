#include "LoopTimer.h"


LoopTimer::LoopTimer(int new_ceiling)
{
	counter = 0;
	ceiling = new_ceiling;
}

bool LoopTimer::ready()
{
	bool result = (++counter >= ceiling);

	counter %= ceiling;
	return result;
}

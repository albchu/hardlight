#include "LoopTimer.h"


LoopTimer::LoopTimer(int new_ceiling, int init_counter)
{
	counter = init_counter;
	ceiling = new_ceiling;
}

bool LoopTimer::ready()
{
	bool result = (++counter >= ceiling);

	counter %= ceiling;
	return result;
}

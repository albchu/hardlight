#ifndef _LOOP_TIMER_H
#define _LOOP_TIMER_H
#include <iostream>
using namespace std;
// Simple object who's intention is to be used to block/approve going into certain calculation expensive blocks of code in OnLoop
class LoopTimer
{
private:
	int counter;
	int ceiling;

public:
	LoopTimer(int new_ceiling, int init_counter=0);
	bool ready();
};

#endif
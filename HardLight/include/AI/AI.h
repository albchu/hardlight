#ifndef _AI_H
#define _AI_H

#include "Vehicle/Bikes.h"

class AI
{
public:
	AI(Bikes* new_bikes);
	void update_bikes();
	void move_bikes();


private:
	Bikes* bikes;

};
#endif
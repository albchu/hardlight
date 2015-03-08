#ifndef _AI_H
#define _AI_H

#include "Vehicle/Bikes.h"
#include "Common.h"
#include <glm/gtx/vector_angle.hpp>

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
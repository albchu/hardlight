#ifndef _AI_H
#define _AI_H

#include "Vehicle/BikeManager.h"
#include "Common.h"
#include <glm/gtx/vector_angle.hpp>

class AI
{
public:
	AI(BikeManager* new_bikes);
	void update_bikes();
	void update_bikes(vec3 pickup);
	void move_bikes();


private:
	BikeManager* bikes;

};
#endif
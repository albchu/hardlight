#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include "Vehicle/Bike.h"

// This class is in charge of moving the bike
class Controller
{
public:
	Controller();
	Controller(Bike* new_bike);
	void forward();
	void backwards();
	void left();
	void right();
	Bike* get_bike();
protected:
	Bike* bike;
};
#endif
#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include "Vehicle/Bike.h"

// This class is in charge of moving the bike
class Controller
{
public:
	typedef void (Controller::*Callback)(Bike*, PxReal);
	Controller();
	Controller(Bike* new_bike);
	void forward(Bike * abike, PxReal acceleration);
	void backwards();
	void left();
	void right();
	void steer(Bike * abike, PxReal steer);
	Bike* get_bike();

	void execute_steering();
	void execute_motion();
	void set_motion(Callback);
	void set_steering(Callback);
	void set_direction(PxReal);
	//void set_bike(Bike* new_bike);
protected:
	Bike* bike;
	PxReal direction;
	PxReal top_acceleration;
	Callback steeringMethod;
	Callback motionMethod;
};
#endif
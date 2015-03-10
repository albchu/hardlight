#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include "Vehicle/Chassis.h"

// This class is in charge of moving the bike
class Controller
{
public:
	typedef void (Controller::*Callback)(Chassis*, PxReal);
	Controller();
	Controller(Chassis* new_bike);
	void forward(Chassis * abike, PxReal acceleration);
	void backwards();
	void left();
	void right();
	void steer(Chassis * abike, PxReal steer);
	Chassis* get_bike();

	void execute_steering();
	void execute_motion();
	void set_motion(Callback);
	void set_steering(Callback);
	void set_direction(PxReal);
	PxReal get_direction();
	void set_acceleration(PxReal);
	PxReal get_acceleration();
	PxReal get_max_acceleration();
	PxReal get_min_acceleration();
	//void set_bike(Chassis* new_bike);
protected:
	Chassis* bike;
	PxReal direction;
	PxReal max_acceleration;
	PxReal min_acceleration;
	PxReal acceleration;
	Callback steeringMethod;
	Callback motionMethod;
};
#endif
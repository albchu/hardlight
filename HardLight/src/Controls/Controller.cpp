#include "Controls/Controller.h"

Controller::Controller(){}

void Controller::forward(Chassis * abike, PxReal acceleration)
{
	abike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	abike->getInputData().setAnalogAccel(acceleration);
}

void Controller::backwards()
{
	chassis->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
	chassis->getInputData().setAnalogAccel(acceleration);
}

void Controller::steer(Chassis * abike, PxReal steer)
{
	// Clamp the steer 
	if(steer < -1.0f)
		steer = -1.0f;
	if(steer > 1.0f)
		steer = 1.0f;
	abike->getInputData().setAnalogSteer(steer);
}

bool Controller::callbacks_set()
{
	return (motionMethod !=NULL && steeringMethod!= NULL);
}

Chassis* Controller::get_chassis()
{
	return chassis;
}

void Controller::execute_steering()
{
	Controller controller;
	(controller.*steeringMethod)(chassis, direction);
	steeringMethod == NULL;
}

void Controller::execute_motion()
{
	Controller controller = Controller();
	(controller.*motionMethod)(chassis, acceleration);
	motionMethod = NULL;
}

void Controller::set_motion(Callback next_motion)
{
	motionMethod = next_motion;
}

void Controller::set_steering(Callback next_steering_method)
{
	steeringMethod = next_steering_method;
}

void Controller::set_direction(PxReal new_direction)
{
	direction = new_direction;
}

PxReal Controller::get_direction()
{
	return direction;
}

void Controller::set_acceleration(PxReal new_acceleration)
{

	acceleration = new_acceleration;
}

PxReal Controller::get_acceleration()
{
	return acceleration;
}

PxReal Controller::get_max_acceleration()
{
	return max_acceleration;
}

PxReal Controller::get_min_acceleration()
{
	return min_acceleration;
}
#include "Controls/Controller.h"

Controller::Controller(){}

void Controller::forward(Chassis * abike, PxReal acceleration)
{
	abike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	abike->getInputData().setAnalogAccel(acceleration);
}

void Controller::backwards()
{
	bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
	bike->getInputData().setAnalogAccel(top_acceleration);
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

void Controller::left()
{
	
}

void Controller::right()
{

}

//void Controller::set_bike(Chassis* new_bike)
//{
//	bike = new_bike;
//}

Chassis* Controller::get_bike()
{
	return bike;
}

void Controller::execute_steering()
{
	Controller controller;
	(controller.*steeringMethod)(bike, direction);
	direction = 0.0;
}

void Controller::execute_motion()
{
	Controller controller = Controller();
	(controller.*motionMethod)(bike, top_acceleration);
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
#include "Controls/Controller.h"

Controller::Controller(){}

void Controller::forward()
{
	bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	bike->getInputData().setAnalogAccel(top_acceleration);
}

void Controller::backwards()
{
	bike->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eREVERSE);
	bike->getInputData().setAnalogAccel(top_acceleration);
}

void Controller::steer(PxReal steer)
{
	// Clamp the steer 
	if(steer < -1.0)
		steer = -1.0;
	if(steer > 1.0)
		steer = 1.0;
	bike->getInputData().setAnalogSteer(steer);
}

void Controller::left()
{

}

void Controller::right()
{

}


Bike* Controller::get_bike()
{
	return bike;
}
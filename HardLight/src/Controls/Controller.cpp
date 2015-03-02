#include "Controls/Controller.h"

Controller::Controller(){}

void Controller::forward()
{
	bike->getInputData().setAnalogAccel(0.250);
}

Bike* Controller::get_bike()
{
	return bike;
}
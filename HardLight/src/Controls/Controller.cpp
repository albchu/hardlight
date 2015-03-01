#include "Controls/Controller.h"

Controller::Controller(){}

void Controller::forward()
{
	bike->getInputData().setAnalogAccel(1.0);
}
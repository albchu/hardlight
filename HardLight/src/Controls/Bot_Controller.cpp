#include "Controls/Bot_Controller.h"

Bot_Controller::Bot_Controller(Chassis* new_chassis)
{
	cout << "Bot controller has been set!" << endl;
	chassis = new_chassis;
	chassis->getVehicle4W()->mDriveDynData.setUseAutoGears(true);
	max_acceleration = 0.75;
	min_acceleration = 0.75;
}

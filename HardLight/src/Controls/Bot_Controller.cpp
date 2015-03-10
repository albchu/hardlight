#include "Controls/Bot_Controller.h"

Bot_Controller::Bot_Controller(Chassis* new_bike)
{
	cout << "Bot controller has been set!" << endl;
	bike = new_bike;
	bike->getVehicle4W()->mDriveDynData.setUseAutoGears(true);
	max_acceleration = 0.75;
	min_acceleration = 0.75;
}

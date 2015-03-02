#include "Controls/Bot_Controller.h"

Bot_Controller::Bot_Controller(Bike* new_bike)
{
	cout << "Bot controller has been set!" << endl;
	bike = new_bike;
	bike->getVehicle4W()->mDriveDynData.setUseAutoGears(true);
	top_acceleration = 0.75;
}

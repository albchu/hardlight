#include "AI/AI.h"

AI::AI(Bikes* new_bikes)
{
	bikes = new_bikes;
}

// Sets the callbacks for controlling the vehicles
void AI::update_bikes()
{
	for(Controller* controllableX: bikes->get_controlled_bikes())
	{
		controllableX->set_motion(&Controller::forward);
		controllableX->set_steering(&Controller::steer);

		for(Controller* controllableY: bikes->get_controlled_bikes())
		{
			// Allow all vehicles to see each other
			if(!controllableY->get_bike()->is_deleted())
			{

				controllableY->set_direction(-0.5);
			}
		}
	}
}

void AI::move_bikes()
{
	for(Controller* controllable: bikes->get_controlled_bikes())
	{
		if(!controllable->get_bike()->is_deleted())
		{
			controllable->execute_motion();
			controllable->execute_steering();
		}
	}
}



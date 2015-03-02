#include "AI/AI.h"

AI::AI(Bikes* new_bikes)
{
	bikes = new_bikes;
}

void AI::update_bikes()
{
	for(Controller* controllable: bikes->get_controlled_bikes())
	{
		if(!controllable->get_bike()->is_deleted())
		{
			controllable->backwards();
			controllable->steer(0.5);
		}
	}
}

void AI::move_bikes()
{

}

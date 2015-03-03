#include "AI/AI.h"

AI::AI(Bikes* new_bikes)
{
	bikes = new_bikes;
}

// Sets the callbacks for controlling the vehicles
void AI::update_bikes()
{
	for(int i = 0; i < bikes->get_controlled_bikes().size(); i++)
	{
		Controller* controllableX = bikes->get_controlled_bikes()[i];
		if(!controllableX->get_bike()->is_deleted())
		{

			vec3 directionX = controllableX->get_bike()->get_direction_vector();
			vec3 positionX = controllableX->get_bike()->get_location();
			float shortest_distance = NULL;
			vec3 target_location = directionX;	// If no better direction is found, the bike will continue going straight forward
			for(int j = 0; j < bikes->get_controlled_bikes().size(); j++)	// Try and find a better target location to go to
			{
				Controller* controllableY = bikes->get_controlled_bikes()[j];
				// Allow all vehicles to see each other
				if(!controllableY->get_bike()->is_deleted() && i != j)	// Only perform calculation if both bikes arnt deleted and arnt the same bike
				{
					vec3 directionY = controllableX->get_bike()->get_direction_vector();
					vec3 positionY = controllableX->get_bike()->get_location();

					//Find direction vector from bikeX to bikeY
					vec3 xy_direction = positionY - positionX;

					//Determine whether this point is in the view of bikeX
					float angle = glm::angle(xy_direction, directionX);

					// Only determine distance between the bikes if bikeX can see bikeY
					if(angle < Common::FORTY_FIVE_DEGREES_RADS)
					{
						float XY_distance = glm::distance(positionY, positionX); // Find distance between the two bikes
						if(shortest_distance == NULL || XY_distance < shortest_distance)
						{
							shortest_distance = XY_distance;
							target_location = positionY;
						}
					}
				}
			}
			// Go to target location
			controllableX->set_motion(&Controller::forward);
			controllableX->set_steering(&Controller::steer);
			float position = (target_location.x-positionX.x)*(directionX.z-positionX.y) - (target_location.x-positionX.y)*(directionX.x-positionX.x);
			cout << "steer degrees: " << position << endl;
			controllableX->set_direction(position);
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



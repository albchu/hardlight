#include "AI/AI.h"

AI::AI(Bikes* new_bikes)
{
	bikes = new_bikes;
}

// Sets the callbacks for controlling the vehicles
void AI::update_bikes()
{
	for(unsigned int i = 0; i < bikes->get_controlled_bikes().size(); i++)
	{

		Controller* controllableX = bikes->get_controlled_bikes()[i];
		if(!controllableX->get_bike()->is_deleted())
		{

			vec3 directionX = controllableX->get_bike()->get_direction_vector();
			vec3 positionX = controllableX->get_bike()->get_location();
			float shortest_distance = NULL;
			vec3 target_location = directionX;	// If no better direction is found, the bike will continue going straight forward
			for(unsigned int j = 0; j < bikes->get_controlled_bikes().size(); j++)	// Try and find a better target location to go to
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
			float dot1 = directionX.x*target_location.x + directionX.z*target_location.z;
			float det1 = directionX.x*target_location.z - directionX.z*target_location.x;
			float angle = -atan2(det1, dot1);

			// Go to target location
			controllableX->set_motion(&Controller::forward);
			controllableX->set_steering(&Controller::steer);
			//cout << "steer degrees: " << position << endl;
			controllableX->set_direction(angle/PxPi);
		}
	}
}

void AI::update_bikes(vec3 pickup)
{
	for(unsigned int i = 0; i < bikes->get_controlled_bikes().size(); i++)
	{
		Controller* controllableX = bikes->get_controlled_bikes()[i];
		if(!controllableX->get_bike()->is_deleted())
		{
			vec3 current_direction = normalize(controllableX->get_bike()->get_direction_vector());
			vec3 current_postion = controllableX->get_bike()->get_location();
			vec3 desired_direction = normalize(pickup - current_postion);
			float dot1 = current_direction.x*desired_direction.x + current_direction.z*desired_direction.z;
			float det1 = current_direction.x*desired_direction.z - current_direction.z*desired_direction.x;
			float angle = -atan2(det1, dot1);
			// Go to target location
			controllableX->set_motion(&Controller::forward);
			controllableX->set_steering(&Controller::steer);
			controllableX->set_direction(angle/PxPi);
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


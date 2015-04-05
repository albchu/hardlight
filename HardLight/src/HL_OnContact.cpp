//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	for(PxU32 i=0; i < nbPairs; i++)
	{
		const PxContactPair& cp = pairs[i];

		if(cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			int iBike, iOther;
			if (cp.shapes[0]->getSimulationFilterData().word0 & EntityTypes::BIKE)
			{
				iBike = 0;
				iOther = 1;
			}
			else if (cp.shapes[1]->getSimulationFilterData().word0 & EntityTypes::BIKE)
			{
				iBike = 1;
				iOther = 0;
			}
			else
			{
				continue;
			}
			Bike* bike = bike_manager->get_bike(pairHeader.actors[iBike]);
			switch (cp.shapes[iOther]->getSimulationFilterData().word0)
			{
			case EntityTypes::GROUND:
				break;
			case EntityTypes::WALL:
				if (find(bikesToKill.begin(), bikesToKill.end(), bike) == bikesToKill.end())
				{	// Only push bike onto bikes to kill vector if it does not already exist
					bikesToKill.push_back(bike);
				}
				break;
			case EntityTypes::BIKE:
				if(find(bikesToKill.begin(), bikesToKill.end(), bike) == bikesToKill.end())
				{	// Only push bike onto bikes to kill vector if it does not already exist
					bikesToKill.push_back(bike);
				}
				bike = bike_manager->get_bike(pairHeader.actors[iOther]);
				if(find(bikesToKill.begin(), bikesToKill.end(), bike) == bikesToKill.end())
				{	// Only push bike onto bikes to kill vector if it does not already exist
					bikesToKill.push_back(bike);
				}
				break;
			}
		}
	}
}

void HardLight::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for(PxU32 i=0; i < count; i++)
	{
		const PxTriggerPair& tp = pairs[i];

		if(tp.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			Bike* bike = bike_manager->get_bike(tp.otherActor);
			switch (tp.triggerShape->getSimulationFilterData().word0)
			{
			case EntityTypes::PICKUP:
				bikePowerupPairs.push_back(tuple<Bike*,PxRigidActor*>(bike, tp.triggerActor));
				if(bike->get_subtype() == PLAYER_BIKE)
				{
					((Player_Controller*)bike->get_controller())->rumble(1.0, 75);
				}
				break;
			case EntityTypes::TAIL:
				Bike* bike = bike_manager->get_bike(tp.otherActor);
				if(find(bikesToKill.begin(), bikesToKill.end(), bike) == bikesToKill.end())
				{	// Only push bike onto bikes to kill vector if it does not already exist
					bikesToKill.push_back(bike);
				}
			}
		}
	}
}
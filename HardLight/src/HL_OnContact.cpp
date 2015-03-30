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
			for (unsigned int i=0; i<2; i++)
			{
				if (cp.shapes[i]->getSimulationFilterData().word0 & EntityTypes::BIKE)
				{
					Bike* bike = bike_manager->get_bike(pairHeader.actors[i]);
					if(find(bikesToKill.begin(), bikesToKill.end(), bike) == bikesToKill.end())
					{	// Only push bike onto bikes to kill vector if it does not already exist
						bikesToKill.push_back(bike);
					}
				}
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
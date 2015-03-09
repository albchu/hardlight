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
			Bike* bike1 = bikes->get_bike(pairHeader.actors[0]);
			Bike* bike2 = bikes->get_bike(pairHeader.actors[1]);
			if (bike1 != NULL)
			{
				if(find(bikesToKill.begin(), bikesToKill.end(), bike1) == bikesToKill.end())
					bikesToKill.push_back(bike1);
			}
			if (bike2 != NULL)
			{
				if(find(bikesToKill.begin(), bikesToKill.end(), bike2) == bikesToKill.end())
					bikesToKill.push_back(bike2);
			}
		}
	}
}

void HardLight::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	for(PxU32 i=0; i < count; i++)
	{
		// ignore pairs when shapes have been deleted
		if (pairs[i].flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
			continue;

		Bike* bike = bikes->get_bike(pairs[i].otherActor);
		if (bike != NULL)
		{
			PxRigidActor* trigger = pairs[i].triggerActor;
			
		}
	}
}
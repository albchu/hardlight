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
			Bike* bike1 = bikes.get_bike(pairHeader.actors[0]);
			Bike* bike2 = bikes.get_bike(pairHeader.actors[1]);
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
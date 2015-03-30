#include "PhysxAgent.h"

PxFilterFlags PhysxAgent::gFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
										PxFilterObjectAttributes attributes1, PxFilterData filterData1,
										PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	if( (0 == (filterData0.word0 & filterData1.word1)) && (0 == (filterData1.word0 & filterData0.word1)) )
		return PxFilterFlag::eSUPPRESS;

	if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
	}
	else
	{
		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
	}

	if ((filterData0.word0 & EntityTypes::BIKE) || (filterData1.word0 & EntityTypes::BIKE))
	{
		pairFlags = pairFlags | PxPairFlag::eNOTIFY_TOUCH_FOUND;
	}

	return PxFilterFlag::eDEFAULT;
}

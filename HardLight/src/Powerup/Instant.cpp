#include "Powerup/Instant.h"

Instant::Instant()
{
	//bike = NULL;
	//bike_manager = NULL;
	//config = NULL;
	//powType = PowerupTypes_SIZE;
	//type = INSTANT;
}

void Instant::extendTail(Chassis* chassis, TailWall* tailwall, INIReader* config, PowerupTimers* powerup_timers)
{
	//vector<TailWall*> tmpTailWall = bike_manager->get_all_tails();
	//for(unsigned int i = 0; i < tmpTailWall.size(); i++)
	//{
	//	if(tmpTailWall[i]->getBike() == bike)
	//	{
	//		tmpTailWall[i]->extend_max_length();
	//		break;
	//	}	
	//}
	tailwall->extend_max_length();
	//bike = NULL;
	return;
}

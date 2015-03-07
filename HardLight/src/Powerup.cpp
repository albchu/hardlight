#include "Powerup.h"

Powerup::Powerup()
{
	bike = NULL;
	bikes = NULL;
	powType = PowerupTypes_SIZE;
}

Powerup::Powerup(Bike* bike, Bikes* bikes)
{
	this->bike=bike;
	this->bikes=bikes;
	powType = PowerupTypes_SIZE;
}

Powerup::~Powerup()									{}
Bike* Powerup::getBike()							{return bike;}
Bikes* Powerup::getBikes()							{return bikes;}
PowerupTypes Powerup::getPowerType()				{return powType;}
void Powerup::setBike(Bike* bike)					{this->bike=bike;}
void Powerup::setBikes(Bikes* bikes)				{this->bikes=bikes;}
void Powerup::setPowerType(PowerupTypes powType)	{this->powType=powType;}

void Powerup::choosePowerup()
{
	powType = (PowerupTypes)(rand() % PowerupTypes_SIZE);
}

void Powerup::choosePowerup(PowerupTypes powType)
{
	this->powType = powType;
}

void Powerup::allocatePowerup()
{
	if(bike->hasPowerup == true || powType == PowerupTypes_SIZE)
	{
		return;
	}
	bike->hasPowerup = true;
}

void Powerup::usePowerup()
{
	if(bike->hasPowerup == true || powType == PowerupTypes_SIZE)
	{
		return;
	}
	switch (powType)
	{
	case EXTENDTAIL:
		this->useExtendTail();
		break;
	case JUMP:
		this->useJump();
		break;
	case INVINCIBLE:
		this->useJump();
		break;
	default:
		break;
	}	
}

void Powerup::useExtendTail()
{
	vector<TailWall*> tmpTailWall = bikes->get_all_tails();
	for(unsigned int i = 0; i < tmpTailWall.size(); i++)
	{
		
	}

}

void Powerup::useJump()
{

}

void Powerup::useInvincible()
{

}


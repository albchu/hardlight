#include "Powerup.h"

Powerup::Powerup()
{
	bike = NULL;
	bikes = NULL;
	config = NULL;
	powType = PowerupTypes_SIZE;
}

Powerup::Powerup(Bike* bike, Bikes* bikes, INIReader* config)
{
	this->bike=bike;
	this->bikes=bikes;
	this->config=config;
	powType = PowerupTypes_SIZE;
}

Powerup::~Powerup()									{}
Bike* Powerup::getBike()							{return bike;}
Bikes* Powerup::getBikes()							{return bikes;}
INIReader* Powerup::getINIReader()					{return config;}
PowerupTypes Powerup::getPowerType()				{return powType;}
void Powerup::setBike(Bike* bike)					{this->bike=bike;}
void Powerup::setBikes(Bikes* bikes)				{this->bikes=bikes;}
void Powerup::setINIReader(INIReader* config)		{this->config=config;}
void Powerup::setPowerType(PowerupTypes powType)	{this->powType=powType;}

void Powerup::choosePowerup()
{
	powType = (PowerupTypes)(rand() % PowerupTypes_SIZE);
}

int Powerup::usePowerup()
{
	if(bike == NULL || powType == PowerupTypes_SIZE)
	{
		return 0;
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
		this->useInvincible();
		break;
	}	
	return 1;
}

void Powerup::useExtendTail()
{
	vector<TailWall*> tmpTailWall = bikes->get_all_tails();
	for(unsigned int i = 0; i < tmpTailWall.size(); i++)
	{
		if(tmpTailWall[i]->getBike() == bike)
		{
			tmpTailWall[i]->extend_max_length();
			break;
		}	
	}
	//bike = NULL;
	return;
}

void Powerup::useJump()
{
	bike->getVehicle4W()->getRigidDynamicActor()->addForce(PxVec3(0.0,(float)config->GetReal("powerup","powerupJumpForce",0.0),0.0),PxForceMode::eIMPULSE);
	//bike = NULL;
	return;
}

void Powerup::useInvincible()
{
	bike->invincible = !bike->invincible;
	// code to make physx actor ignore collisions
	//bike = NULL;
	return;
}

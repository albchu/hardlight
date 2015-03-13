#include "Powerup.h"

Powerup::Powerup()
{
	bike = NULL;
	bike_manager = NULL;
	config = NULL;
	powType = PowerupTypes_SIZE;
}

Powerup::Powerup(Bike* bike, BikeManager* bike_manager, INIReader* config)
{
	this->bike=bike;
	this->bike_manager=bike_manager;
	this->config=config;
	powType = PowerupTypes_SIZE;
}

Powerup::~Powerup()									
{

}

Bike* Powerup::getBike()
{
	return bike;
}

BikeManager* Powerup::getBikes()							
{
	return bike_manager;
}

INIReader* Powerup::getINIReader()					
{
	return config;
}

PowerupTypes Powerup::getPowerType()			
{
	return powType;
}

void Powerup::setBike(Bike* bike)					
{
	this->bike=bike;
}

void Powerup::setBikes(BikeManager* bike_manager)				
{
	this->bike_manager=bike_manager;
}

void Powerup::setINIReader(INIReader* config)		
{
	this->config=config;
}

void Powerup::setPowerType(PowerupTypes powType)	
{
	this->powType=powType;
}

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
		bike->get_chassis()->toggle_invincible();
		break;
	}	
	return 1;
}

void Powerup::useExtendTail()
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
	bike->get_tail()->extend_max_length();
	//bike = NULL;
	return;
}

void Powerup::useJump()
{
	//PxVec3 negation = PxVec3(0.0,0.0,0.0);
	//negation = bike->getVehicle4W()->getRigidDynamicActor()->getAngularVelocity();
	//negation = -negation;
	//bike->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(negation,PxForceMode::eIMPULSE);
	//std::cout << "Torque neutralized" << std::endl;

	bike->get_chassis()->getVehicle4W()->getRigidDynamicActor()->addForce(PxVec3(0.0,100.0,0.0),PxForceMode::eIMPULSE);
	bike->get_chassis()->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(PxVec3(0.0,0.0,0.0),PxForceMode::eVELOCITY_CHANGE);
	bike->get_chassis()->getVehicle4W()->getRigidDynamicActor()->clearTorque();
	bike->get_chassis()->getVehicle4W()->getRigidDynamicActor()->addForce(PxVec3(0.0,(float)config->GetReal("powerup","powerupJumpForce",0.0),0.0),PxForceMode::eIMPULSE);
	//PxVec3 negation = PxVec3(0.0,0.0,0.0);
	//bike->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(negation,PxForceMode::eIMPULSE);
	//PxVec3 temp = bike->getVehicle4W()->getRigidDynamicActor()->getAngularVelocity();
	//std::cout << "Angular Velocity: " << temp.x << " " << temp.y << " " << temp.z << " " << std::endl;
	//bike = NULL;
	return;
}


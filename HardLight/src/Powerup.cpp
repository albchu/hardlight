#include "Powerup.h"

//This constructor shouldnt be necessary
Powerup::Powerup()
{
	//bike = NULL;
	//bike_manager = NULL;
	//config = NULL;
	//powType = PowerupTypes_SIZE;
}

//Powerup::Powerup(Bike* bike, BikeManager* bike_manager, INIReader* config)
//{
//	this->bike=bike;
//	this->bike_manager=bike_manager;
//	this->config=config;
//	//powType = PowerupTypes_SIZE;
//}

Powerup<T>::~Powerup()									
{
	// I dont understand why you guys make these if you dont put anything in them
}
//
//Bike* Powerup::getBike()
//{
//	return bike;
//}
//
//BikeManager* Powerup::getBikes()							
//{
//	return bike_manager;
//}
//
//INIReader* Powerup::getINIReader()					
//{
//	return config;
//}
//
//void Powerup::setBike(Bike* bike)					
//{
//	this->bike=bike;
//}
//
//void Powerup::setBikes(BikeManager* bike_manager)				
//{
//	this->bike_manager=bike_manager;
//}
//
//void Powerup::setINIReader(INIReader* config)		
//{
//	this->config=config;
//}

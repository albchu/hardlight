#include "Hold.h"

Hold::Hold()
{
	//bike = NULL;
	//bike_manager = NULL;
	//config = NULL;
//	powType = PowerupTypes_SIZE;
	type = HOLD;
}

void Hold::jump(Chassis* chassis, TailWall* tailwall, INIReader* config)
{
	//PxVec3 negation = PxVec3(0.0,0.0,0.0);
	//negation = bike->getVehicle4W()->getRigidDynamicActor()->getAngularVelocity();
	//negation = -negation;
	//bike->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(negation,PxForceMode::eIMPULSE);
	//std::cout << "Torque neutralized" << std::endl;

	chassis->getVehicle4W()->getRigidDynamicActor()->addForce(PxVec3(0.0,100.0,0.0),PxForceMode::eIMPULSE);
	chassis->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(PxVec3(0.0,0.0,0.0),PxForceMode::eVELOCITY_CHANGE);
	chassis->getVehicle4W()->getRigidDynamicActor()->clearTorque();
	chassis->getVehicle4W()->getRigidDynamicActor()->addForce(PxVec3(0.0,(float)config->GetReal("powerup","powerupJumpForce",0.0),0.0),PxForceMode::eIMPULSE);
	//PxVec3 negation = PxVec3(0.0,0.0,0.0);
	//bike->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(negation,PxForceMode::eIMPULSE);
	//PxVec3 temp = bike->getVehicle4W()->getRigidDynamicActor()->getAngularVelocity();
	//std::cout << "Angular Velocity: " << temp.x << " " << temp.y << " " << temp.z << " " << std::endl;
	//bike = NULL;
	return;
}

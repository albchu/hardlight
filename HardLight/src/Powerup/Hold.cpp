#include "Powerup/Hold.h"

Hold::Hold()
{
	//bike = NULL;
	//bike_manager = NULL;
	//config = NULL;
	//	powType = PowerupTypes_SIZE;
	//type = HOLD;
}

void Hold::jump(Chassis* chassis, TailWall* tailwall, INIReader* config, PowerupTimers* powerup_timers)
{
	//PxVec3 negation = PxVec3(0.0,0.0,0.0);
	//negation = bike->getVehicle4W()->getRigidDynamicActor()->getAngularVelocity();
	//negation = -negation;
	//bike->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(negation,PxForceMode::eIMPULSE);
	//std::cout << "Torque neutralized" << std::endl;

	chassis->getVehicle4W()->getRigidDynamicActor()->addForce(PxVec3(0.0,100.0,0.0),PxForceMode::eIMPULSE);
	chassis->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(PxVec3(0.0,0.0,0.0));
	chassis->getVehicle4W()->getRigidDynamicActor()->clearTorque();
	chassis->getVehicle4W()->getRigidDynamicActor()->addForce(PxVec3(0.0,(float)config->GetReal("powerup","powerupJumpForce",0.0),0.0),PxForceMode::eIMPULSE);
	//PxVec3 negation = PxVec3(0.0,0.0,0.0);
	//bike->getVehicle4W()->getRigidDynamicActor()->setAngularVelocity(negation,PxForceMode::eIMPULSE);
	//PxVec3 temp = bike->getVehicle4W()->getRigidDynamicActor()->getAngularVelocity();
	//std::cout << "Angular Velocity: " << temp.x << " " << temp.y << " " << temp.z << " " << std::endl;
	//bike = NULL;
	return;
}

void Hold::ghost(Chassis* chassis, TailWall* tailwall, INIReader* config, PowerupTimers* powerup_timers)
{
	// Set ghost_timer to the current system time; set using_ghost flag to true
	powerup_timers->ghost_timer = clock();
	powerup_timers->using_ghost = true;

	// Activate ghost ability
	chassis->set_invincible(true);
}

void Hold::super_saiyen(Chassis* chassis, TailWall* tailwall, INIReader* config, PowerupTimers* powerup_timers)
{
	// Set super_saiyen_timer to the current system time; set using_super_saiyen to true
	powerup_timers->super_saiyen_timer = clock();
	powerup_timers->using_super_saiyen = true;

	// Activate super saiyen ability
	tailwall->set_width((float)config->GetReal("powerup","ss_wall_width",1.0));
	tailwall->set_height((float)config->GetReal("powerup","ss_wall_height",10.0));
}


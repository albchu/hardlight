#include "Vehicle/CreateVehicle.h"

CreateVehicle::CreateVehicle(INIReader* new_config, PhysxAgent* new_pxAgent)
{
	config = new_config;
	pxAgent = new_pxAgent;
	
}

//==============================================================================
VehicleDesc initVehicleDesc(PxMaterial* gMaterial, INIReader* config)
{
	//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
	//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
	//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.
	const PxF32 chassisMass = (float)config->GetReal("bike", "chassisMass", 1500.0);
	const PxVec3 chassisDims(2.5f,2.0f,8.0f);
	const PxVec3 chassisMOI
		((chassisDims.y*chassisDims.y + chassisDims.z*chassisDims.z)*chassisMass/(float)config->GetReal("bike", "chassisMoIFactor", 12.0),
		 (chassisDims.x*chassisDims.x + chassisDims.z*chassisDims.z)*0.8f*chassisMass/(float)config->GetReal("bike", "chassisMoIFactor", 12.0),
		 (chassisDims.x*chassisDims.x + chassisDims.y*chassisDims.y)*chassisMass/(float)config->GetReal("bike", "chassisMoIFactor", 12.0));

	const PxF32 centerOfMassX = (float)config->GetReal("bike", "centerOfMassX", 0.0);
	const PxF32 centerOfMassY = (float)config->GetReal("bike", "centerOfMassY", -chassisDims.y*0.5f - 0.65f);
	const PxF32 centerOfMassZ = (float)config->GetReal("bike", "centerOfMassZ", 0.0);
	const PxVec3 chassisCMOffset(centerOfMassX, centerOfMassY, centerOfMassZ);
	//const PxVec3 chassisCMOffset(0.0f, -chassisDims.y*0.5f - 0.65f, 0.25f);

	//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
	//Moment of inertia is just the moment of inertia of a cylinder.
	const PxF32 wheelMass = (float)config->GetReal("bike", "wheelMass", 20.0);
	const PxF32 wheelRadius = (float)config->GetReal("bike", "wheelRadius", 0.5f);
	const PxF32 wheelWidth = (float)config->GetReal("bike", "wheelWidth", 0.4f);
	const PxF32 wheelMOI = (float)config->GetReal("bike", "wheelMoIFactor", 0.5f)*wheelMass*wheelRadius*wheelRadius;
	const PxU32 nbWheels = 4;

	VehicleDesc vehicleDesc;
	vehicleDesc.chassisMass = chassisMass;
	vehicleDesc.chassisDims = chassisDims;
	vehicleDesc.chassisMOI = chassisMOI;
	vehicleDesc.chassisCMOffset = chassisCMOffset;
	vehicleDesc.chassisMaterial = gMaterial;
	vehicleDesc.wheelMass = wheelMass;
	vehicleDesc.wheelRadius = wheelRadius;
	vehicleDesc.wheelWidth = wheelWidth;
	vehicleDesc.wheelMOI = wheelMOI;
	vehicleDesc.numWheels = nbWheels;
	vehicleDesc.wheelMaterial = gMaterial;
	return vehicleDesc;
}

//==============================================================================
bool CreateVehicle::Create(Chassis* &chassis, PxVec3 init_position, PxVec3 init_facing, PxVec3 init_up)
{
	PxMaterial* gMaterial = pxAgent->get_physics()->createMaterial(2.0f, 2.0f, 0.6f);
	//Create the batched scene queries for the suspension raycasts.
	chassis->setVehicleSceneQueryData(VehicleSceneQueryData::allocate(1, PX_MAX_NB_WHEELS, 1, pxAgent->get_allocator()));
	chassis->setBatchQuery(VehicleSceneQueryData::setUpBatchedSceneQuery(0, *chassis->getVehicleSceneQueryData(), pxAgent->get_scene()));
	
	//Create a vehicle that will drive on the plane.
	VehicleDesc vehicleDesc = initVehicleDesc(gMaterial, config);
	chassis->setVehicle4W(createVehicle4W(vehicleDesc, pxAgent->get_physics(), pxAgent->get_cooking(), config));
	PxTransform startTransform(init_position, PhysxAgent::PxLookAt(init_facing, init_up));
	chassis->getVehicle4W()->getRigidDynamicActor()->setGlobalPose(startTransform);
	pxAgent->get_scene()->addActor(*chassis->getVehicle4W()->getRigidDynamicActor());

	//bike = new Chassis(bike->getVehicle4W()->getRigidDynamicActor(), "../data/BikeTexture.tga");
	chassis->set_actor(chassis->getVehicle4W()->getRigidDynamicActor());
	chassis->init_opengl();

	//vehicle = bike->getVehicle4W()->getRigidDynamicActor();

	//Set the vehicle to rest in first gear.
	//Set the vehicle to use auto-gears.
	chassis->getVehicle4W()->setToRestState();
	chassis->getVehicle4W()->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	chassis->getVehicle4W()->mDriveDynData.setUseAutoGears(true);

	chassis->setInAir(true);
	return true;
}
//==============================================================================
#include "HardLight.h"

//==============================================================================
VehicleDesc initVehicleDesc(PxMaterial* gMaterial, INIReader* config)
{
	//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
	//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
	//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.
	const PxF32 chassisMass = config->GetReal("bike", "chassisMass", 1500.0f);
	const PxVec3 chassisDims(2.5f,2.0f,8.0f);
	const PxVec3 chassisMOI
		((chassisDims.y*chassisDims.y + chassisDims.z*chassisDims.z)*chassisMass/(config->GetReal("bike", "chassisMoIFactor", 12.0f)),
		 (chassisDims.x*chassisDims.x + chassisDims.z*chassisDims.z)*0.8f*chassisMass/(config->GetReal("bike", "chassisMoIFactor", 12.0f)),
		 (chassisDims.x*chassisDims.x + chassisDims.y*chassisDims.y)*chassisMass/(config->GetReal("bike", "chassisMoIFactor", 12.0f)));

	const PxF32 centerOfMassX = config->GetReal("bike", "centerOfMassX", 0.0);
	const PxF32 centerOfMassY = config->GetReal("bike", "centerOfMassY", -chassisDims.y*0.5f - 0.65f);
	const PxF32 centerOfMassZ = config->GetReal("bike", "centerOfMassZ", 0.0);
	const PxVec3 chassisCMOffset(centerOfMassX, centerOfMassY, centerOfMassZ);
	//const PxVec3 chassisCMOffset(0.0f, -chassisDims.y*0.5f - 0.65f, 0.25f);

	//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
	//Moment of inertia is just the moment of inertia of a cylinder.
	const PxF32 wheelMass = config->GetReal("bike", "wheelMass", 20.0);
	const PxF32 wheelRadius = config->GetReal("bike", "wheelRadius", 0.5f);
	const PxF32 wheelWidth = config->GetReal("bike", "wheelWidth", 0.4f);
	const PxF32 wheelMOI = config->GetReal("bike", "wheelMoIFactor", 0.5f)*wheelMass*wheelRadius*wheelRadius;
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
bool HardLight::CreateVehicle(PxVec3 init_position)
{
	gMaterial = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);

	//Create the batched scene queries for the suspension raycasts.
	gVehicleSceneQueryData = VehicleSceneQueryData::allocate(1, PX_MAX_NB_WHEELS, 1, gDefaultAllocator);
	gBatchQuery = VehicleSceneQueryData::setUpBatchedSceneQuery(0, *gVehicleSceneQueryData, gScene);
	
	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);
	
	//Create a plane to drive on.
	gGroundPlane = createDrivablePlane(gMaterial, gPhysics);
	gScene->addActor(*gGroundPlane);
	Entity* ground = new Entity(gGroundPlane, mesh_map.getEntityMesh("plane"), "../data/uvgrid.tga");
	world.add_entity(ground);

	//Create a vehicle that will drive on the plane.
	VehicleDesc vehicleDesc = initVehicleDesc(gMaterial, config);
	gVehicle4W = createVehicle4W(vehicleDesc, gPhysics, gCooking, config);
	PxTransform startTransform(init_position, PxQuat(PxIdentity));
	gVehicle4W->getRigidDynamicActor()->setGlobalPose(startTransform);
	gScene->addActor(*gVehicle4W->getRigidDynamicActor());

	gVehicle4W->getRigidDynamicActor()->setName("bike");
	Entity* bike = new Bike(gVehicle4W->getRigidDynamicActor(), mesh_map.getEntityMesh("HardLightBike"), "../data/BikeTexture.tga");
	world.add_entity(bike);

	vehicle = gVehicle4W->getRigidDynamicActor();

	//Set the vehicle to rest in first gear.
	//Set the vehicle to use auto-gears.
	gVehicle4W->setToRestState();
	gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	gVehicle4W->mDriveDynData.setUseAutoGears(true);

	gIsVehicleInAir = true;
	return true;
}
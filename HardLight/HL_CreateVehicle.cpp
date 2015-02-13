//==============================================================================
#include "HardLight.h"

//==============================================================================
VehicleDesc initVehicleDesc(PxMaterial* gMaterial)
{
	//Set up the chassis mass, dimensions, moment of inertia, and center of mass offset.
	//The moment of inertia is just the moment of inertia of a cuboid but modified for easier steering.
	//Center of mass offset is 0.65m above the base of the chassis and 0.25m towards the front.
	const PxF32 chassisMass = 1500.0f;
	const PxVec3 chassisDims(2.5f,2.0f,5.0f);
	const PxVec3 chassisMOI
		((chassisDims.y*chassisDims.y + chassisDims.z*chassisDims.z)*chassisMass/12.0f,
		 (chassisDims.x*chassisDims.x + chassisDims.z*chassisDims.z)*0.8f*chassisMass/12.0f,
		 (chassisDims.x*chassisDims.x + chassisDims.y*chassisDims.y)*chassisMass/12.0f);
	const PxVec3 chassisCMOffset(0.0f, -chassisDims.y*0.5f + 0.65f, 0.25f);

	//Set up the wheel mass, radius, width, moment of inertia, and number of wheels.
	//Moment of inertia is just the moment of inertia of a cylinder.
	const PxF32 wheelMass = 20.0f;
	const PxF32 wheelRadius = 0.5f;
	const PxF32 wheelWidth = 0.4f;
	const PxF32 wheelMOI = 0.5f*wheelMass*wheelRadius*wheelRadius;
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
bool HardLight::CreateVehicle()
{
	gMaterial = gPhysics->createMaterial(1.9f, 1.9f, 0.6f);

	//Create the batched scene queries for the suspension raycasts.
	gVehicleSceneQueryData = VehicleSceneQueryData::allocate(1, PX_MAX_NB_WHEELS, 1, gDefaultAllocator);
	gBatchQuery = VehicleSceneQueryData::setUpBatchedSceneQuery(0, *gVehicleSceneQueryData, gScene);
	
	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);
	
	//Create a plane to drive on.
	gGroundPlane = createDrivablePlane(gMaterial, gPhysics);
	gScene->addActor(*gGroundPlane);

	vector<vec3> plane_mesh;
	plane_mesh.push_back(vec3(0.0f, -10.0f, -10.0f));
	plane_mesh.push_back(vec3(0.0f, 10.0f, -10.0f));
	plane_mesh.push_back(vec3(0.0f, 10.0f, 10.0f));
	plane_mesh.push_back(vec3(0.0f, -10.0f, 10.0f));

	world.add_entity(gGroundPlane, plane_mesh);

	//Create a vehicle that will drive on the plane.
	VehicleDesc vehicleDesc = initVehicleDesc(gMaterial);
	gVehicle4W = createVehicle4W(vehicleDesc, gPhysics, gCooking);
	PxTransform startTransform(PxVec3(0, (vehicleDesc.chassisDims.y*0.5f + vehicleDesc.wheelRadius + 10.0f), 0), PxQuat(PxIdentity));
	gVehicle4W->getRigidDynamicActor()->setGlobalPose(startTransform);
	gScene->addActor(*gVehicle4W->getRigidDynamicActor());

	vector<vec3> vehicle_mesh;
	vehicle_mesh.push_back(vec3(-1.0f, 0.0f, -1.0f));
	vehicle_mesh.push_back(vec3(1.0f, 0.0f, -1.0f));
	vehicle_mesh.push_back(vec3(1.0f, 0.0f, 1.0f));
	vehicle_mesh.push_back(vec3(-1.0f, 0.0f, 1.0f));

	world.add_entity(gVehicle4W->getRigidDynamicActor(), vehicle_mesh);
	vehicle = gVehicle4W->getRigidDynamicActor();

	//Set the vehicle to rest in first gear.
	//Set the vehicle to use auto-gears.
	gVehicle4W->setToRestState();
	gVehicle4W->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	gVehicle4W->mDriveDynData.setUseAutoGears(true);

	gIsVehicleInAir = true;
	return true;
}
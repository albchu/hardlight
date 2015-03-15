#include "PhysxAgent.h"

int PhysxAgent::getNbCores()
{
	return 4;
}

PhysxAgent::PhysxAgent(INIReader* new_config, PxSimulationEventCallback* pxSimulationEventCallback)
{
	config = new_config;
	tail_mesh = NULL;
	pickup_mesh = NULL;
	ground_mesh = NULL;

	// Initialize foundation
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	if(!gFoundation)
		cerr << "Could not initialize physx foundation" << endl;


	// Initialize dispatcher
	PxU32 numWorkers = PxMax(PxI32(getNbCores()), 0);
	if (numWorkers == 0)
		cerr << "Could not initialize physx numWorkers" << endl;

	numWorkers--;
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	if (!gDispatcher)
		cerr << "Could not initialize physx dispatcher" << endl;

	// Initialize the physx physics
	PxProfileZoneManager* profileZoneManager = &PxProfileZoneManager::createProfileZoneManager(gFoundation);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, profileZoneManager);
	if(gPhysics == NULL)
		cerr << "Could not initialize physx physics" << endl;

	if(!PxInitExtensions(*gPhysics))
		cerr << "Could not initialize physx extensions" << endl;

	if(!PxInitVehicleSDK(*gPhysics))
		cerr << "Could not initialize physx vehicle sdk" << endl;

	PxVehicleSetBasisVectors(PxVec3(0,1,0), PxVec3(0,0,1));
	PxVehicleSetUpdateMode(PxVehicleUpdateMode::eVELOCITY_CHANGE);

	if(gPhysics->getPvdConnectionManager())
	{
		gPhysics->getVisualDebugger()->setVisualDebuggerFlag(PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
		gConnection = PxVisualDebuggerExt::createConnection(gPhysics->getPvdConnectionManager(), "127.0.0.1", 5425, 10, PxVisualDebuggerConnectionFlag::eDEBUG);
	}


	// Initialize the physx scene
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PhysxAgent::gFilterShader;
	sceneDesc.simulationEventCallback = pxSimulationEventCallback;

	gScene = gPhysics->createScene(sceneDesc);
	if(!gScene)
		cerr << "Could not initialize physx scene" << endl;

	//Initialize the physx cooking
	gCooking = 	PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));
	if(!gCooking)
		cerr << "Could not initialize physx cooking" << endl;

}

void PhysxAgent::cleanup()
{
	PxCloseExtensions();
	PxCloseVehicleSDK();
	if (gCooking != NULL) gCooking->release();
	if (gScene != NULL) gScene->release();
	if (gDispatcher != NULL) gDispatcher->release();
	if (gConnection != NULL) gConnection->release();
	if (gPhysics != NULL) gPhysics->release();
	if (gFoundation != NULL) gFoundation->release();
}

PxPhysics* PhysxAgent::get_physics()
{
	return gPhysics;
}

PxScene* PhysxAgent::get_scene()
{
	return gScene;
}

PxFoundation* PhysxAgent::get_foundation()
{
	return gFoundation;
}

PxDefaultCpuDispatcher* PhysxAgent::get_dispatcher()
{
	return gDispatcher;
}


vec3 PhysxAgent::toVec3(PxVec3 pxvec3)
{
	return vec3(pxvec3.x, pxvec3.y, pxvec3.z);
}

PxDefaultAllocator PhysxAgent::get_allocator()
{
	return gAllocator;
}

PxDefaultErrorCallback PhysxAgent::get_error_callback()
{
	return gErrorCallback;
}

PxCooking* PhysxAgent::get_cooking()
{
	return gCooking;
}


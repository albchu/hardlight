#include "PhysxAgent.h"

PxFilterFlags Physx_Agent::gFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, 
										 PxFilterObjectAttributes attributes1, PxFilterData filterData1,
										 PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	// let triggers through
	if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}

	if( (0 == (filterData0.word0 & filterData1.word1)) && (0 == (filterData1.word0 & filterData0.word1)) )
		return PxFilterFlag::eSUPPRESS;

	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	if (((filterData0.word0 & COLLISION_FLAG_CHASSIS) && (filterData1.word0 & COLLISION_FLAG_OBSTACLE))
		|| ((filterData0.word0 & COLLISION_FLAG_CHASSIS) && (filterData1.word0 & COLLISION_FLAG_CHASSIS))
		|| ((filterData0.word0 & COLLISION_FLAG_OBSTACLE) && (filterData1.word0 & COLLISION_FLAG_CHASSIS))
		)
	{
		pairFlags = pairFlags | PxPairFlag::eNOTIFY_TOUCH_FOUND;
	}

	return PxFilterFlag::eDEFAULT;
}

int Physx_Agent::getNbCores()
{
	return 4;
}

Physx_Agent::Physx_Agent(INIReader* new_config)
{
	config = new_config;

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
	sceneDesc.gravity = PxVec3(
		(float)config->GetReal("gravity", "x", 0.0),
		(float)config->GetReal("gravity", "y", 0.0),
		(float)config->GetReal("gravity", "z", 0.0)
		);
	sceneDesc.filterShader = Physx_Agent::gFilterShader;
	//sceneDesc.simulationEventCallback = this;

	gScene = gPhysics->createScene(sceneDesc);
	if(!gScene)
		cerr << "Could not initialize physx scene" << endl;


}

void Physx_Agent::cleanup()
{
	if (gScene != NULL) gScene->release();
	if (gDispatcher != NULL) gDispatcher->release();
	//PxCloseExtensions();
	if (gConnection != NULL) gConnection->release();

	if (gPhysics != NULL) gPhysics->release();
	if (gFoundation != NULL) gFoundation->release();
}

PxPhysics* Physx_Agent::get_physics()
{
	return gPhysics;
}

PxScene* Physx_Agent::get_scene()
{
	return gScene;
}

PxFoundation* Physx_Agent::get_foundation()
{
	return gFoundation;
}

PxDefaultCpuDispatcher* Physx_Agent::get_dispatcher()
{
	return gDispatcher;
}


vec3 Physx_Agent::toVec3(PxVec3 pxvec3)
{
	return vec3(pxvec3.x, pxvec3.y, pxvec3.z);
}

PxDefaultAllocator Physx_Agent::get_allocator()
{
	return gAllocator;
}

PxDefaultErrorCallback Physx_Agent::get_error_callback()
{
	return gErrorCallback;
}

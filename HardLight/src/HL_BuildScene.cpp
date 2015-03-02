//==============================================================================
#include "HardLight.h"
#include "TailSegment.h"
#include "MeshMap.h"

//==============================================================================

bool HardLight::BuildScene()
{
	skybox = new SkyBox(gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f))), MeshMap::Instance()->getEntityMesh("skybox.obj"), "../data/Textures/MoonSkybox.tga");
	world.add_entity(skybox);

	PxMaterial* gMaterial = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);

	//Create a plane to drive on.
	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *gMaterial);

	//Get the plane shape so we can set query and simulation filter data.
	PxShape* shapes[1];
	groundPlane->getShapes(shapes, 1);

	//Set the query filter data of the ground plane so that the vehicle raycasts can hit the ground.
	PxFilterData qryFilterData;
	qryFilterData.word3 = (PxU32)DRIVABLE_SURFACE;
	shapes[0]->setQueryFilterData(qryFilterData);

	//Set the simulation filter data of the ground plane so that it collides with the chassis of a vehicle but not the wheels.
	PxFilterData simFilterData;
	simFilterData.word0 = COLLISION_FLAG_GROUND;
	simFilterData.word1 = COLLISION_FLAG_GROUND_AGAINST;
	shapes[0]->setSimulationFilterData(simFilterData);

	gScene->addActor(*groundPlane);
	Entity* ground = new Entity(groundPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), "../data/Textures/TronTile3.tga");
	world.add_entity(ground);
	
	//walls
	qryFilterData.word3 = (PxU32)UNDRIVABLE_SURFACE;
	simFilterData.word0 = COLLISION_FLAG_OBSTACLE;
	simFilterData.word1 = COLLISION_FLAG_OBSTACLE_AGAINST;
	size = (float)config->GetReal("scene", "size", 1000.0);

	PxRigidStatic* wallPlane = PxCreatePlane(*gPhysics, PxPlane(1.0f,0.0f,0.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	gScene->addActor(*wallPlane);
	Entity* wall = new Entity(wallPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), "../data/Textures/TronTile3.tga");
	world.add_entity(wall);

	wallPlane = PxCreatePlane(*gPhysics, PxPlane(-1.0f,0.0f,0.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	gScene->addActor(*wallPlane);
	wall = new Entity(wallPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), "../data/Textures/TronTile3.tga");
	world.add_entity(wall);

	wallPlane = PxCreatePlane(*gPhysics, PxPlane(0.0f,0.0f,1.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	gScene->addActor(*wallPlane);
	wall = new Entity(wallPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), "../data/Textures/TronTile3.tga");
	world.add_entity(wall);

	wallPlane = PxCreatePlane(*gPhysics, PxPlane(0.0f,0.0f,-1.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	gScene->addActor(*wallPlane);
	wall = new Entity(wallPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), "../data/Textures/TronTile3.tga");
	world.add_entity(wall);
	
	CreateVehicle vehicleCreator = CreateVehicle(config, gScene, gPhysics, gAllocator, gFoundation);

	for (int i=0; i < config->GetInteger("game", "numBots", 0) ; i++)
	{
		Bike* new_bike = new Bike();
		if(!vehicleCreator.Create(new_bike, PxVec3((i%2) ? (10.0f*i) : (-10.0f*i), 5.0f, 50.0f)))
			return false;
		world.add_entity(new_bike);
		bikes.add_bot_bike(new_bike);
		//Controller * controllerz = new Bot_Controller(new_bike);
		//controllableBikes.push_back(controllerz);
	}

	for (int i = 0 ; i < config->GetInteger("game", "numPlayers", 1) ; i++)
	{
		Bike* new_bike = new Bike();
		if(!vehicleCreator.Create(new_bike, PxVec3(0,5,0)))
			return false;
		world.add_entity(new_bike);
		new_bike->invincible = config->GetBoolean("game", "playerInvincible", false);
		if (controllers.size() > 0)
			bikes.add_player_bike(new_bike, controllers[i]);
		else
			bikes.add_player_bike(new_bike, NULL);
	}

	if (controllers.size() > 0)
	{
		controller = new Bot_Controller(bikes.get_bot_bikes()[0]);
		//controller = new Player_Controller(bikes.get_player_bikes()[0], controllers[0]);
	}
		
	
	sfxMix.PlayMusic(0);

	return true;
}
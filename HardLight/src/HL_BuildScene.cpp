#include "HardLight.h"

bool HardLight::BuildScene()
{
	skybox = new SkyBox(pxAgent->get_physics()->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f))), MeshMap::Instance()->getEntityMesh("skybox.obj"), "../data/Textures/MoonSkybox.tga");
	world.add_entity(skybox);

	PxMaterial* gMaterial = pxAgent->get_physics()->createMaterial(2.0f, 2.0f, 0.6f);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);

	//Create a plane to drive on.
	PxRigidStatic* groundPlane = PxCreatePlane(*pxAgent->get_physics(), PxPlane(0,1,0,0), *gMaterial);

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

	pxAgent->get_scene()->addActor(*groundPlane);
	Entity* ground = new Entity(groundPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile3.tga"));
	ground->set_type(FLOOR);
	world.add_entity(ground);

	//walls
	qryFilterData.word3 = (PxU32)UNDRIVABLE_SURFACE;
	simFilterData.word0 = COLLISION_FLAG_OBSTACLE;
	simFilterData.word1 = COLLISION_FLAG_OBSTACLE_AGAINST;
	float size = (float)config->GetReal("scene", "size", 1000.0);

	PxRigidStatic* wallPlane = PxCreatePlane(*pxAgent->get_physics(), PxPlane(1.0f,0.0f,0.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	pxAgent->get_scene()->addActor(*wallPlane);
	Wall* wall = new Wall(wallPlane, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"));
	world.add_entity(wall);

	wallPlane = PxCreatePlane(*pxAgent->get_physics(), PxPlane(-1.0f,0.0f,0.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	pxAgent->get_scene()->addActor(*wallPlane);
	wall = new Wall(wallPlane, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"));
	world.add_entity(wall);

	wallPlane = PxCreatePlane(*pxAgent->get_physics(), PxPlane(0.0f,0.0f,1.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	pxAgent->get_scene()->addActor(*wallPlane);
	wall = new Wall(wallPlane, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"));
	world.add_entity(wall);

	wallPlane = PxCreatePlane(*pxAgent->get_physics(), PxPlane(0.0f,0.0f,-1.0f,size), *gMaterial);
	wallPlane->getShapes(shapes, 1);
	shapes[0]->setQueryFilterData(qryFilterData);
	shapes[0]->setSimulationFilterData(simFilterData);
	pxAgent->get_scene()->addActor(*wallPlane);
	wall = new Wall(wallPlane, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"));
	world.add_entity(wall);

	CreateVehicle vehicleCreator = CreateVehicle(config, pxAgent);

	vector<PxVec3> start_locations;
	float offset = size-10.0f;
	float height = 5.0f;
	start_locations.push_back(PxVec3(offset, height, offset));
	start_locations.push_back(PxVec3(-offset, height, -offset));
	start_locations.push_back(PxVec3(-offset, height, offset));
	start_locations.push_back(PxVec3(offset, height, -offset));
	start_locations.push_back(PxVec3(offset, height, 0.0f));
	start_locations.push_back(PxVec3(-offset, height, 0.0f));
	start_locations.push_back(PxVec3(0.0f, height, offset));
	start_locations.push_back(PxVec3(0.0f, height, -offset));

	for (int i = 0; i < config->GetInteger("game", "numPlayers", 1); i++)
	{
		Chassis* new_chassis = new Chassis();
		if (i < start_locations.size())
		{
			if(!vehicleCreator.Create(new_chassis, start_locations[i]))
				return false;
		}
		else
		{
			if(!vehicleCreator.Create(new_chassis, PxVec3(50.0f, 5.0f, (i%2) ? (10.0f*i) : (-10.0f*i))))
				return false;
		}

		new_chassis->set_invincible(config->GetBoolean("game", "playerInvincible", false));


		// Add a menu to scene CURRENTLY BAD. BLAME ALBERT
		menu = new Menu(pxAgent->get_physics()->createRigidStatic(PxTransform(0.0f, 0.0f, 0.0f)), new_chassis);
		world.add_entity(menu);

		Camera* aCamera = new Camera(config, new_chassis->get_actor());
		viewports[i].camera = aCamera;	// We will only have numPlayers number of viewports so it stands that we should only initialize the same amount of cameras

		if (controllers.size() > 0 && !config->GetBoolean("game", "disableControllers", false))
			bike_manager->add_player_bike(new_chassis, controllers[i]);
		else
			bike_manager->add_player_bike(new_chassis, NULL);
	}


	for (int i=0; i < config->GetInteger("game", "numBots", 0); i++)
	{
		Chassis* new_chassis = new Chassis();
		int position = bike_manager->get_player_bikes().size() + i;

		if (position < start_locations.size())
		{
			if(!vehicleCreator.Create(new_chassis, start_locations[position]))
				return false;
		}
		else
		{
			if(!vehicleCreator.Create(new_chassis, PxVec3((i%2) ? (10.0f*i) : (-10.0f*i), 5.0f, 50.0f)))
				return false;
		}

		//PxTransform somepose = new_chassis->get_actor()->getGlobalPose();
		bike_manager->add_bot_bike(new_chassis);

	}

	//pickup = new Pickup(config, pxAgent, size);
	//world.add_entity(pickup);

	sfxMix.PlayMusic("musicOverworld");

	// Init Powerup object for testing powerup functionality temporarily
	powerup_manager->spawn_random_powerup(vec3(0,0,0));

	return true;
}
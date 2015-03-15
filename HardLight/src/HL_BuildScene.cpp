#include "HardLight.h"

bool HardLight::spawnBikes() {
	CreateVehicle vehicleCreator = CreateVehicle(config, pxAgent);

	vector<PxVec3> start_locations;
	size = (float)config->GetReal("scene", "size", 1000.0);
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

	if(bikes->get_player_bikes().size() < 1) {
		for (unsigned int i = 0; i < (unsigned int)config->GetInteger("game", "numPlayers", 1); i++)
		{
			Bike* new_bike = new Bike();
			if (i < start_locations.size())
			{
				if(!vehicleCreator.Create(new_bike, start_locations[i]))
					return false;
			}
			else
			{
				if(!vehicleCreator.Create(new_bike, PxVec3(50.0f, 5.0f, (i%2) ? (10.0f*i) : (-10.0f*i))))
					return false;
			}

			new_bike->invincible = config->GetBoolean("game", "playerInvincible", false);
			if (controllers.size() > 0)
				bikes->add_player_bike(new_bike, controllers[i]);
			else
				bikes->add_player_bike(new_bike, NULL);
		}
	}

	for (int i=0; i < config->GetInteger("game", "numBots", 0); i++)
	{
		Bike* new_bike = new Bike();
		unsigned int position = bikes->get_player_bikes().size() + i;

		if (position < start_locations.size())
		{
			if(!vehicleCreator.Create(new_bike, start_locations[position]))
				return false;
		}
		else
		{
			if(!vehicleCreator.Create(new_bike, PxVec3((i%2) ? (10.0f*i) : (-10.0f*i), 5.0f, 50.0f)))
				return false;
		}

		PxTransform somepose = new_bike->get_actor()->getGlobalPose();
		bikes->add_bot_bike(new_bike);

	}

	return true;
}

bool HardLight::BuildScene()
{
	skybox = new SkyBox(pxAgent->get_physics()->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f))), MeshMap::Instance()->getEntityMesh("skybox.obj"), "../data/Textures/MoonSkybox.tga");
	world.add_entity(skybox);

	PxMaterial* gMaterial = pxAgent->get_physics()->createMaterial(2.0f, 2.0f, 0.6f);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);
	/*
	//Create a plane to drive on.
	PxRigidStatic* ground_plane = PxCreatePlane(*pxAgent->get_physics(), PxPlane(0,1,0,0), *gMaterial);

	//Get the plane shape so we can set query and simulation filter data.
	PxShape* shapes[1];
	ground_plane->getShapes(shapes, 1);

	//Set the query filter data of the ground plane so that the vehicle raycasts can hit the ground.
	PxFilterData qryFilterData;
	qryFilterData.word3 = (PxU32)DRIVABLE_SURFACE;
	shapes[0]->setQueryFilterData(qryFilterData);

	//Set the simulation filter data of the ground plane so that it collides with the chassis of a vehicle but not the wheels.
	PxFilterData simFilterData;
	simFilterData.word0 = COLLISION_FLAG_GROUND;
	simFilterData.word1 = COLLISION_FLAG_GROUND_AGAINST;
	shapes[0]->setSimulationFilterData(simFilterData);

	pxAgent->get_scene()->addActor(*ground_plane);
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
	*/
	vec3 scale_factor(size, size, size);
	PxRigidStatic* ground_actor = pxAgent->create_ground(scale_factor);
	Entity* ground = new Entity(ground_actor, MeshMap::Instance()->getEntityMesh("cube.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile1.tga"), scale_factor);
	world.add_entity(ground);

	CreateVehicle vehicleCreator = CreateVehicle(config, pxAgent);

	vector<PxVec3> start_locations;
	//float offset = size-10.0f;
	float height = size+10.0f;
	start_locations.push_back(PxVec3(0.0f, height, 0.0f));
	start_locations.push_back(PxVec3(0.0f, -height, 0.0f));
	start_locations.push_back(PxVec3(height, 0.0f, 0.0f));
	start_locations.push_back(PxVec3(-height, 0.0f, 0.0f));
	start_locations.push_back(PxVec3(0.0f, 0.0f, height));
	start_locations.push_back(PxVec3(0.0f, 0.0f, -height));

	if(bikes->get_player_bikes().size() < 1) {
		for (unsigned int i = 0; i < (unsigned int)config->GetInteger("game", "numPlayers", 1); i++)
		{
			Bike* new_bike = new Bike();
			if (i < start_locations.size())
			{
				if(!vehicleCreator.Create(new_bike, start_locations[i]))
					return false;
			}
			else
			{
				if(!vehicleCreator.Create(new_bike, PxVec3(50.0f, height, (i%2) ? (10.0f*i) : (-10.0f*i))))
					return false;
			}

			new_bike->invincible = config->GetBoolean("game", "playerInvincible", false);


			// Add a menu to scene CURRENTLY BAD. BLAME ALBERT
			menu = new Menu(pxAgent->get_physics()->createRigidStatic(PxTransform(0.0f, 0.0f, 0.0f)), new_bike);
			world.add_entity(menu);

			if (controllers.size() > 0)
				bikes->add_player_bike(new_bike, controllers[i]);
			else
				bikes->add_player_bike(new_bike, NULL);
		}
	}

	for (unsigned int i=0; i < (unsigned int)config->GetInteger("game", "numBots", 0); i++)
	{
		Bike* new_bike = new Bike();
		unsigned int position = bikes->get_player_bikes().size() + i;

		if (position < start_locations.size())
		{
			if(!vehicleCreator.Create(new_bike, start_locations[position]))
				return false;
		}
		else
		{
			if(!vehicleCreator.Create(new_bike, PxVec3((i%2) ? (10.0f*i) : (-10.0f*i), height, 50.0f)))
				return false;
		}

		PxTransform somepose = new_bike->get_actor()->getGlobalPose();
		bikes->add_bot_bike(new_bike);

	}

	pickup = new Pickup(config, pxAgent, size);
	world.add_entity(pickup);

	sfxMix.PlayMusic("musicOverworld");

	// Init Powerup object for testing powerup functionality temporarily
	powerup->setBike(bikes->get_player_bikes()[0]);

	return true;
}
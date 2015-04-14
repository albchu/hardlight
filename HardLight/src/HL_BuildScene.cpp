#include "HardLight.h"

bool HardLight::BuildScene()
{

	// Initialize viewport info. Moved into build scene due to num players being able to be changed in menu after init is called
	loading_update("Generating viewports");
	int cams = glm::max(config->GetInteger("game", "numCameras", 1), (long)numPlayers);
	viewports = Viewports::generate_viewports(cams, window_width, window_height);

	loading_update("Loading variables");
	maxParticles = config->GetInteger("particles", "count", 100) / config->GetInteger("game", "numCameras", 1);
	particleSpeed = (float)config->GetReal("particles", "speed", 10);
	explosionLifeSpan = config->GetReal("particles", "lifetime", 5000.0f);
	loading_update("Initializing partical data");
	particleData = ParticleData(maxParticles);

	powerUpMessage = "";

	PxMaterial* gMaterial = pxAgent->get_physics()->createMaterial(2.0f, 2.0f, 0.6f);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);

	vector<PxVec3> start_locations;
	vector<PxVec3> start_facing;
	vector<PxVec3> start_up;
	float height = 0.f;
	vec3 scale_factor(size, size, size);

	loading_update("Importing objects");
	MeshMap::Instance();

	loading_update("Building skybox");
	skybox = new SkyBox(pxAgent->get_physics()->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f))), MeshMap::Instance()->getEntityMesh("skybox.obj"), TextureMap::Instance()->getTexture("../data/Textures/MoonSkybox.tga"));
	world.add_entity(skybox);

	if (map_type == MapTypes::SPHERE)
	{
		loading_update("Creating sphere world");

		PxRigidStatic* ground_actor = pxAgent->create_ground_sphere(size);
		Entity* ground = new Entity(ground_actor, MeshMap::Instance()->getEntityMesh("WorldSphere.obj"), TextureMap::Instance()->getTexture("../data/Textures/WorldSphere.tga"), scale_factor);
		world.add_entity(ground);

		height = size+5.0f;
		start_locations.push_back(PxVec3(0.0f, height, 0.0f));
		start_facing.push_back(PxVec3(1.f, 0.f, 0.f));
		start_locations.push_back(PxVec3(0.0f, -height, 0.0f));
		start_facing.push_back(PxVec3(-1.f, 0.f, 0.f));
		start_locations.push_back(PxVec3(height, 0.0f, 0.0f));
		start_facing.push_back(PxVec3(0.f, -1.f, 0.f));
		start_locations.push_back(PxVec3(-height, 0.0f, 0.0f));
		start_facing.push_back(PxVec3(0.f, 1.f, 0.f));
		start_locations.push_back(PxVec3(0.0f, 0.0f, height));
		start_facing.push_back(PxVec3(1.f, 0.f, 0.f));
		start_locations.push_back(PxVec3(0.0f, 0.0f, -height));
		start_facing.push_back(PxVec3(-1.f, 0.f, 0.f));
		for (unsigned int i=0; i<start_locations.size(); i++)
			start_up.push_back(start_locations[i].getNormalized());
	}
	else if (map_type == MapTypes::PLANE)
	{
		loading_update("Creating arena world");

		PxRigidStatic* actor = pxAgent->create_ground_plane();
		Entity* ground = new Entity(actor, MeshMap::Instance()->getEntityMesh("plane.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"), scale_factor);
		world.add_entity(ground);

		//walls
		PxRigidStatic* wall_actor = pxAgent->create_wall_plane(PxPlane(1.f,0.f,0.f,size));
		Wall* wall = new Wall(wall_actor, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"), scale_factor);
		world.add_entity(wall);

		wall_actor = pxAgent->create_wall_plane(PxPlane(-1.f,0.f,0.f,size));
		wall = new Wall(wall_actor, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"), scale_factor);
		world.add_entity(wall);

		wall_actor = pxAgent->create_wall_plane(PxPlane(0.f,0.f,1.f,size));
		wall = new Wall(wall_actor, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"), scale_factor);
		world.add_entity(wall);

		wall_actor = pxAgent->create_wall_plane(PxPlane(0.f,0.f,-1.f,size));
		wall = new Wall(wall_actor, MeshMap::Instance()->getEntityMesh("arenaWall.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"), scale_factor);
		world.add_entity(wall);

		float offset = size-10.0f;
		height = 5.0f;
		start_locations.push_back(PxVec3(offset, height, offset));
		start_facing.push_back(PxVec3(-1.f, 0.f, -1.f));
		start_locations.push_back(PxVec3(-offset, height, -offset));
		start_facing.push_back(PxVec3(1.f, 0.f, 1.f));
		start_locations.push_back(PxVec3(offset, height, -offset));
		start_facing.push_back(PxVec3(-1.f, 0.f, 1.f));
		start_locations.push_back(PxVec3(-offset, height, offset));
		start_facing.push_back(PxVec3(1.f, 0.f, -1.f));
		start_locations.push_back(PxVec3(offset, height, 0.f));
		start_facing.push_back(PxVec3(-1.f, 0.f, 0.f));
		start_locations.push_back(PxVec3(-offset, height, 0.f));
		start_facing.push_back(PxVec3(1.f, 0.f, 0.f));
		start_locations.push_back(PxVec3(0.f, height, offset));
		start_facing.push_back(PxVec3(0.f, 0.f, -1.f));
		start_locations.push_back(PxVec3(0.f, height, -offset));
		start_facing.push_back(PxVec3(0.f, 0.f, 1.f));
		for (unsigned int i=0; i<start_locations.size(); i++)
			start_up.push_back(PxVec3(0.f, 1.f, 0.f));
	}

	CreateVehicle vehicleCreator = CreateVehicle(config, pxAgent);
	unsigned int count = 0;
	loading_update("Populating world with players");

	for (unsigned int i=0; i < (unsigned int)numPlayers; i++)
	{
		if (count < start_locations.size())
		{
			Chassis* new_chassis = new Chassis();
			if(!vehicleCreator.Create(new_chassis, start_locations[count], start_facing[count], start_up[count]))
				return false;
			new_chassis->set_invincible(config->GetBoolean("game", "playerInvincible", false));

			if (controllers.size() > i && !config->GetBoolean("game", "disableControllers", false))
				bike_manager->add_player_bike(new_chassis, controllers[i]);
			else
				bike_manager->add_player_bike(new_chassis, NULL);

			if (count < viewports.size())
			{
				bike_manager->get_bike(new_chassis->get_actor())->set_id(viewports[count].id);
				Camera* aCamera = new Camera(config, new_chassis->get_actor(), viewports[count].width, viewports[count].height, map_type);
				viewports[count].camera = aCamera;
			}

			count++;
		}
	}

	loading_update("Populating world with bots");

	for (unsigned int i=0; i < (unsigned int)numBots; i++)
	{
		if (count < start_locations.size())
		{
			Chassis* new_chassis = new Chassis();

			if(!vehicleCreator.Create(new_chassis, start_locations[count], start_facing[count], start_up[count]))
				return false;

			bike_manager->add_bot_bike(new_chassis);

			if (count < viewports.size())
			{
				bike_manager->get_bike(new_chassis->get_actor())->set_id(viewports[count].id);
				Camera* aCamera = new Camera(config, new_chassis->get_actor(), viewports[count].width, viewports[count].height, map_type);
				viewports[count].camera = aCamera;
			}

			count++;
		}

	}

	if (count < viewports.size())
	{
		vector <Bike*> bikes = bike_manager->get_all_bikes();

		for (;count < viewports.size(); count++)
		{
			Camera* aCamera = new Camera(config, bikes[count%bikes.size()]->get_chassis()->get_actor(), viewports[count].width, viewports[count].height, map_type);
			viewports[count].camera = aCamera;
		}
	}

	start_locations.clear();
	start_facing.clear();
	start_up.clear();

	loading_update("Setting up powerups");

	// Init Powerup object for testing powerup functionality temporarily
	for(int i = 0; i < numHoldPowerups; i++)
	{
		powerup_manager->spawn_hold_powerup();
	}
	for(int i = 0; i < numHoldPowerups; i++)
	{
		powerup_manager->spawn_instant_powerup();
	}
	powerup_manager->spawn_instant_powerup();	// Always make at least one instant powerup

	scene_built = true;

	return true;
}
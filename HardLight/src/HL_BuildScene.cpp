#include "HardLight.h"

bool HardLight::BuildScene()
{
	skybox = new SkyBox(pxAgent->get_physics()->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f))), MeshMap::Instance()->getEntityMesh("skybox.obj"), "../data/Textures/MoonSkybox.tga");
	world.add_entity(skybox);

	PxMaterial* gMaterial = pxAgent->get_physics()->createMaterial(2.0f, 2.0f, 0.6f);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);

	vector<PxVec3> start_locations;
	vector<PxVec3> start_facing;
	vector<PxVec3> start_up;
	float height = 0.f;
	vec3 scale_factor(size, size, size);

	if (map_type == MapTypes::SPHERE)
	{
		PxRigidStatic* ground_actor = pxAgent->create_ground_sphere(size);
		Entity* ground = new Entity(ground_actor, MeshMap::Instance()->getEntityMesh("sphere.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"), scale_factor);
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
		for (int i=0; i<start_locations.size(); i++)
			start_up.push_back(start_locations[i]);

		CreateVehicle vehicleCreator = CreateVehicle(config, pxAgent);

	}
	else if (map_type == MapTypes::PLANE)
	{
		PxRigidStatic* ground_actor = pxAgent->create_ground_plane();
		Entity* ground = new Entity(ground_actor, MeshMap::Instance()->getEntityMesh("plane.obj"), TextureMap::Instance()->getTexture("../data/Textures/TronTile2.tga"), scale_factor);
		world.add_entity(ground);

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
		for (int i=0; i<start_locations.size(); i++)
			start_up.push_back(PxVec3(0.f, 1.f, 0.f));
	}

	CreateVehicle vehicleCreator = CreateVehicle(config, pxAgent);
	unsigned int start = 0;

	for (unsigned int i = 0; i < (unsigned int)config->GetInteger("game", "numPlayers", 1); i++)
	{
		if (start < start_locations.size())
		{
			Bike* new_bike = new Bike();
			if(!vehicleCreator.Create(new_bike, start_locations[start], start_facing[start], start_up[start]))
				return false;
			start++;
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
		if (start < start_locations.size())
		{
			Bike* new_bike = new Bike();

			if(!vehicleCreator.Create(new_bike, start_locations[start], start_facing[start], start_up[start]))
				return false;
			start++;
			bikes->add_bot_bike(new_bike);
		}
	}

	pickup = new Pickup(config, pxAgent, size);
	world.add_entity(pickup);

	sfxMix.PlayMusic("musicOverworld");

	// Init Powerup object for testing powerup functionality temporarily
	powerup->setBike(bikes->get_player_bikes()[0]);

	return true;
}
//==============================================================================
#include "HardLight.h"
#include "TailSegment.h"
#include "MeshMap.h"

//==============================================================================

bool HardLight::BuildScene()
{
	sfxMix.PlayMusic(0);

	skybox = new SkyBox(gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f))), MeshMap::Instance()->getEntityMesh("skybox.obj"), "../data/Textures/MoonSkybox.tga");
	world.add_entity(skybox);

	gMaterial = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);

	//Create the friction table for each combination of tire and surface type.
	gFrictionPairs = createFrictionPairs(gMaterial);

	//Create a plane to drive on.
	gGroundPlane = createDrivablePlane(gMaterial, gPhysics);
	gScene->addActor(*gGroundPlane);
	Entity* ground = new Entity(gGroundPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), "../data/Textures/TronTile.tga");
	world.add_entity(ground);

	return true;
}
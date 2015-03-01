//==============================================================================
#include "HardLight.h"
#include "TailWall.h"
#include "MeshMap.h"

//==============================================================================


bool HardLight::BuildScene()
{
	sfxMix.InitializeMixer(config);
	sfxMix.PlayMusic(0);

	skybox = new SkyBox(gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f))), MeshMap::Instance()->getEntityMesh("skybox.obj"), "../data/Textures/MoonSkybox.tga");
	world.add_entity(skybox);

	//PxMaterial* ground_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);

	////Create the batched scene queries for the suspension raycasts.
	//bike->setVehicleSceneQueryData(VehicleSceneQueryData::allocate(1, PX_MAX_NB_WHEELS, 1, gDefaultAllocator));
	//bike->setBatchQuery(VehicleSceneQueryData::setUpBatchedSceneQuery(0, *bike->getVehicleSceneQueryData(), gScene));
	//
	////Create the friction table for each combination of tire and surface type.
	//gFrictionPairs = createFrictionPairs(ground_material);
	//
	////Create a plane to drive on.
	//gGroundPlane = createDrivablePlane(ground_material, gPhysics);
	//gScene->addActor(*gGroundPlane);
	//Entity* ground = new Entity(gGroundPlane, MeshMap::Instance()->getEntityMesh("plane.obj"), "../data/Textures/uvgrid.tga");
	//world.add_entity(ground);


	//PxMaterial* planeMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.2f);
	//PxMaterial* cubeMaterial = gPhysics->createMaterial(0.1f, 0.4f, 1.0f);
	//PxMaterial* sphereMaterial = gPhysics->createMaterial(0.6f, 0.1f, 0.1f);

	//// *** Create Ground-Plane *** //
	//PxTransform pose = PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f)));
	//PxRigidStatic* gGroundPlane = gPhysics->createRigidStatic(pose);
	//PxShape* shape = gGroundPlane->createShape(PxPlaneGeometry(), *planeMaterial);
	//gScene->addActor(*gGroundPlane);

	//vector<vec3> plane_mesh;
	////plane_mesh.push_back(vec3(0.0f, -10.0f, -10.0f));
	////plane_mesh.push_back(vec3(0.0f, 10.0f, -10.0f));
	////plane_mesh.push_back(vec3(0.0f, 10.0f, 10.0f));
	////plane_mesh.push_back(vec3(0.0f, -10.0f, 10.0f));
	//plane_mesh.push_back(vec3(-25.0f, 25.0f, -20.0f));
	//plane_mesh.push_back(vec3(25.0f, 25.0f, -20.0f));
	//plane_mesh.push_back(vec3(-25.0f, -25.0f, -20.0f));
	//plane_mesh.push_back(vec3(25.0f, -25.0f, -20.0f));

	//world.add_entity(gGroundPlane, plane_mesh);
	

	//world.add_entity(*plane, Mesh::createPlaneMesh());
	//
	//// *** Create Wall-Planes *** //
	//PxTransform leftPose = PxTransform(PxVec3(0.0f, 0.0f, size), PxQuat(PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
	//PxRigidStatic* leftPlane = gPhysics->createRigidStatic(leftPose);
	//PxShape* leftShape = leftPlane->createShape(PxPlaneGeometry(), *planeMaterial);
	//gScene->addActor(*leftPlane);
	////world.add_entity(*leftPlane, Mesh::createPlaneMesh());

	//PxTransform rightPose = PxTransform(PxVec3(-size, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f)));
	//PxRigidStatic* rightPlane = gPhysics->createRigidStatic(rightPose);
	//PxShape* rightShape = rightPlane->createShape(PxPlaneGeometry(), *planeMaterial);
	//gScene->addActor(*rightPlane);
	////world.add_entity(*rightPlane, Mesh::createPlaneMesh());

	//PxTransform leftPose2 = PxTransform(PxVec3(0.0f, 0.0f, -size), PxQuat(PxHalfPi, PxVec3(0.0f, -1.0f, 0.0f)));
	//PxRigidStatic* leftPlane2 = gPhysics->createRigidStatic(leftPose2);
	//PxShape* leftShape2 = leftPlane2->createShape(PxPlaneGeometry(), *planeMaterial);
	//gScene->addActor(*leftPlane2);
	////world.add_entity(*leftPlane2, Mesh::createPlaneMesh());

	//PxTransform rightPose2 = PxTransform(PxVec3(size, 0.0f, 0.0f), PxQuat(PxPi, PxVec3(0.0f, 1.0f, 0.0f)));
	//PxRigidStatic* rightPlane2 = gPhysics->createRigidStatic(rightPose2);
	//PxShape* rightShape2 = rightPlane2->createShape(PxPlaneGeometry(), *planeMaterial);
	//gScene->addActor(*rightPlane2);
	////world.add_entity(*rightPlane2, Mesh::createPlaneMesh());
	//
	//// Initialize Sphere Actor
	//PxReal sphereDensity = 2.0f;
	//PxTransform sphereTransform(PxVec3(0.0f, 4.0f, 0.0f));
	//PxSphereGeometry sphereGeometry(0.7f);
	//for (int i=0; i<nbObjects; i++)
	//{
	//	sphereTransform.p  = PxVec3(0.0f,4.0f+4*i,0.0f);

	//	PxRigidDynamic *sphereActor = PxCreateDynamic(*gPhysics, sphereTransform, sphereGeometry, *sphereMaterial, sphereDensity);
	//	if (!sphereActor) return false;

	//	sphereActor->setAngularDamping((PxReal)0.2);
	//	sphereActor->setLinearDamping((PxReal)0.01);
	//	sphereActor->setMass((PxReal)(1.0+(i/4.0)));
	//	gScene->addActor(*sphereActor);
	//	//world.add_entity(*sphereActor);
	//}
	return true;
}
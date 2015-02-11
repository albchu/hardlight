//==============================================================================
#include "HardLight.h"

//==============================================================================
bool HardLight::BuildScene()
{
	PxMaterial* planeMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.2f);
	PxMaterial* cubeMaterial = gPhysics->createMaterial(0.1f, 0.4f, 1.0f);
	PxMaterial* sphereMaterial = gPhysics->createMaterial(0.6f, 0.1f, 0.1f);

	// *** Create Ground-Plane *** //
	PxTransform pose = PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidStatic* plane = gPhysics->createRigidStatic(pose);
	PxShape* shape = plane->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*plane);
	vector<vec3> *mesh;
	world.add_entity(*plane, Mesh::createPlaneMesh());
	
	// *** Create Wall-Planes *** //
	PxTransform leftPose = PxTransform(PxVec3(0.0f, 0.0f, size), PxQuat(PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
	PxRigidStatic* leftPlane = gPhysics->createRigidStatic(leftPose);
	PxShape* leftShape = leftPlane->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*leftPlane);
	world.add_entity(*leftPlane, Mesh::createPlaneMesh());

	PxTransform rightPose = PxTransform(PxVec3(-size, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f)));
	PxRigidStatic* rightPlane = gPhysics->createRigidStatic(rightPose);
	PxShape* rightShape = rightPlane->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*rightPlane);
	world.add_entity(*rightPlane, Mesh::createPlaneMesh());

	PxTransform leftPose2 = PxTransform(PxVec3(0.0f, 0.0f, -size), PxQuat(PxHalfPi, PxVec3(0.0f, -1.0f, 0.0f)));
	PxRigidStatic* leftPlane2 = gPhysics->createRigidStatic(leftPose2);
	PxShape* leftShape2 = leftPlane2->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*leftPlane2);
	world.add_entity(*leftPlane2, Mesh::createPlaneMesh());

	PxTransform rightPose2 = PxTransform(PxVec3(size, 0.0f, 0.0f), PxQuat(PxPi, PxVec3(0.0f, 1.0f, 0.0f)));
	PxRigidStatic* rightPlane2 = gPhysics->createRigidStatic(rightPose2);
	PxShape* rightShape2 = rightPlane2->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*rightPlane2);
	world.add_entity(*rightPlane2, Mesh::createPlaneMesh());
	
	// Initialize Sphere Actor
	PxReal sphereDensity = 2.0f;
	PxTransform sphereTransform(PxVec3(0.0f, 4.0f, 0.0f));
	PxSphereGeometry sphereGeometry(0.7f);
	for (int i=0; i<nbObjects; i++)
	{
		sphereTransform.p  = PxVec3(0.0f,4.0f+4*i,0.0f);

		PxRigidDynamic *sphereActor = PxCreateDynamic(*gPhysics, sphereTransform, sphereGeometry, *sphereMaterial, sphereDensity);
		if (!sphereActor) return false;

		sphereActor->setAngularDamping((PxReal)0.2);
		sphereActor->setLinearDamping((PxReal)0.01);
		sphereActor->setMass((PxReal)(1.0+(i/4.0)));
		gScene->addActor(*sphereActor);
		world.add_entity(*sphereActor);
	}
	return true;
}
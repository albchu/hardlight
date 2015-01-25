//==============================================================================
#include "HardLight.h"

//==============================================================================
bool HardLight::BuildScene()
{
	PxMaterial* planeMaterial = gPhysics->createMaterial(0.9f, 0.1f, 1.0f);
	PxMaterial* cubeMaterial = gPhysics->createMaterial(0.1f, 0.4f, 1.0f);
	PxMaterial* sphereMaterial = gPhysics->createMaterial(0.6f, 0.1f, 0.6f);

	// *** Create Ground-Plane *** //
	PxTransform pose = PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidStatic* plane = gPhysics->createRigidStatic(pose);
	PxShape* shape = plane->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*plane);

	// *** Create Wall-Planes *** //
	PxTransform leftPose = PxTransform(PxVec3(0.0f, 0.0f, 10.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
	PxRigidStatic* leftPlane = gPhysics->createRigidStatic(leftPose);
	PxShape* leftShape = leftPlane->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*leftPlane);

	PxTransform rightPose = PxTransform(PxVec3(-10.0f, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f)));
	PxRigidStatic* rightPlane = gPhysics->createRigidStatic(rightPose);
	PxShape* rightShape = rightPlane->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*rightPlane);

	PxTransform leftPose2 = PxTransform(PxVec3(0.0f, 0.0f, -10.0f), PxQuat(PxHalfPi, PxVec3(0.0f, -1.0f, 0.0f)));
	PxRigidStatic* leftPlane2 = gPhysics->createRigidStatic(leftPose2);
	PxShape* leftShape2 = leftPlane2->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*leftPlane2);

	PxTransform rightPose2 = PxTransform(PxVec3(10.0f, 0.0f, 0.0f), PxQuat(PxPi, PxVec3(0.0f, 1.0f, 0.0f)));
	PxRigidStatic* rightPlane2 = gPhysics->createRigidStatic(rightPose2);
	PxShape* rightShape2 = rightPlane2->createShape(PxPlaneGeometry(), *planeMaterial);
	gScene->addActor(*rightPlane2);

	// Initialize Cube Actor
	PxReal cubeDensity = 2.0f;
	PxTransform cubeTransform(PxVec3(0.0f, 4.0, 0.0f));
	PxVec3 cubeDims(0.5,0.5,0.5);
	PxBoxGeometry cubeGeometry(cubeDims);
	for (int i=0; i<nbObjects; i++)// Loop for number of objects
	{
		cubeTransform.p  = PxVec3(0.0f,4.0f+5*i,0.0f);

		PxRigidDynamic *cubeActor = PxCreateDynamic(*gPhysics, cubeTransform, cubeGeometry, *cubeMaterial, cubeDensity);
		if (!cubeActor) return false;

		cubeActor->setAngularDamping((PxReal)0.2);
		cubeActor->setLinearDamping((PxReal)0.01);
		cubeActor->setMass((PxReal)(1.0+(i/8.0)));
		gScene->addActor(*cubeActor);
		boxes.push_back(cubeActor);
	}

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
		spheres.push_back(sphereActor);
	}
	return true;
}
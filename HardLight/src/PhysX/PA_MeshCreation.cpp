#include "PhysxAgent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

static PxU32 driveable(EntityTypes type)
{
	switch (type)
	{
	case GROUND:
		return DRIVABLE_SURFACE;
		break;
	default:
		return UNDRIVABLE_SURFACE;
		break;
	}
}

static PxU32 collides_with(EntityTypes type)
{
	switch (type)
	{
	case WALL:
		return BIKE;
		break;
	case BIKE:
		return WALL | BIKE | GROUND | PICKUP;
		break;
	case GROUND:
		return BIKE;
		break;
	case PICKUP:
		return BIKE;
		break;
	default:
		return 0;
		break;
	}
}

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
static quat RotationBetweenVectors(vec3 start, vec3 dest)
{
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
		if (length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(PxPi, rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return quat(
		s * 0.5f, 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
		);
}

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
PxQuat PhysxAgent::PxLookAt(vec3 direction, vec3 up)
{
	normalize(direction);
	normalize(up);
	// Find the rotation between the front of the object (that we assume towards +Z, 
	// but this depends on your model) and the desired direction 
	quat rot1 = RotationBetweenVectors(vec3(0.0f, 0.0f, 1.0f), direction);
	// Recompute desiredUp so that it's perpendicular to the direction
	// You can skip that part if you really want to force desiredUp
	vec3 right = cross(direction, up);
	up = cross(right, direction);

	// Because of the 1rst rotation, the up is probably completely screwed up. 
	// Find the rotation between the "up" of the rotated object, and the desired up
	vec3 newUp = rot1 * up;
	quat rot2 = RotationBetweenVectors(newUp, up);

	quat targetOrientation = rot2 * rot1; // remember, in reverse order
	return PxQuat(targetOrientation.x, targetOrientation.y, targetOrientation.z, targetOrientation.w);
}

PxQuat PhysxAgent::PxLookAt(PxVec3 direction, PxVec3 up)
{
	return PxLookAt(toVec3(direction), toVec3(up));
}

PxConvexMesh* PhysxAgent::create_convex_mesh(vector<vec3> vertices)
{
	vector<PxVec3> vs;
	for(unsigned int i=0; i<vertices.size(); i++)
	{
		vs.push_back(PxVec3(vertices[i].x, vertices[i].y, vertices[i].z));
	}

	PxConvexMeshDesc convexDesc;
	convexDesc.points.count     = vs.size();
	convexDesc.points.stride    = sizeof(PxVec3);
	convexDesc.points.data      = vs.data();
	convexDesc.flags            = PxConvexFlag::eCOMPUTE_CONVEX | PxConvexFlag::eINFLATE_CONVEX;
	convexDesc.vertexLimit      = 256;

	PxConvexMesh* convexMesh = NULL;
	PxDefaultMemoryOutputStream buf;
	if(gCooking->cookConvexMesh(convexDesc, buf))
	{
		PxDefaultMemoryInputData id(buf.getData(), buf.getSize());
		convexMesh = gPhysics->createConvexMesh(id);
	}

	return convexMesh;
}

PxRigidStatic* PhysxAgent::create_tail(vec3 old_location, vec3 new_location, vec3 up, float width, float height)
{
	float save_y = new_location.y;
	old_location.y = 0.0f;
	new_location.y = 0.0f;
	if (tail_mesh == NULL)
	{
		MeshData* tail_data = MeshMap::Instance()->getEntityMesh("tail.obj");
		tail_mesh = create_convex_mesh(*tail_data->getVertices());
		tail_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	}
	vec3 direction = normalize(old_location - new_location); // from new to old
	float distance = glm::distance(vec3(old_location.x, 0.0f, old_location.z), vec3(new_location.x, 0.0f, new_location.z));
	if (distance < 0.001f)
	{
		direction = vec3(0.0f, 0.0f, 1.0f);
		distance = 0.001f;
	}

	PxTransform transform(PxVec3(new_location.x, save_y, new_location.z), PxLookAt(direction, up));
	PxMeshScale scale(PxVec3(width, height, distance), PxQuat(PxIdentity));

	PxFilterData simFilterData;
	EntityTypes type = EntityTypes::WALL;
	simFilterData.word0 = type;
	simFilterData.word1 = collides_with(type);
	PxFilterData queryFilterData;
	queryFilterData.word3 = driveable(type);

	PxRigidStatic* actor = gPhysics->createRigidStatic(transform);
	PxShape* shape = actor->createShape(PxConvexMeshGeometry(tail_mesh, scale), *tail_material);
	shape->setQueryFilterData(queryFilterData);
	shape->setSimulationFilterData(simFilterData);
	shape->setLocalPose(PxTransform(PxIdentity));
	gScene->addActor(*actor);
	return actor;
}

PxRigidStatic* PhysxAgent::create_pickup(vec3 location, vec3 up, vec3 scaleFactors)
{
	if (pickup_mesh == NULL)
	{
		MeshData* pickup_data = MeshMap::Instance()->getEntityMesh("tail.obj");
		pickup_mesh = create_convex_mesh(*pickup_data->getVertices());
		pickup_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	}

	PxFilterData simFilterData;
	EntityTypes type = EntityTypes::PICKUP;
	simFilterData.word0 = type;
	simFilterData.word1 = collides_with(type);
	PxFilterData queryFilterData;
	queryFilterData.word3 = driveable(type);

	PxTransform transform(PxVec3(location.x, location.y, location.z));
	PxMeshScale scale(PxVec3(scaleFactors.x, scaleFactors.y, scaleFactors.z), PxQuat(PxIdentity));

	PxRigidStatic* actor = gPhysics->createRigidStatic(transform);
	PxShape* shape = actor->createShape(PxConvexMeshGeometry(pickup_mesh, scale), *pickup_material);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	shape->setQueryFilterData(queryFilterData);
	shape->setSimulationFilterData(simFilterData);
	shape->setLocalPose(PxTransform(PxIdentity));
	gScene->addActor(*actor);
	return actor;
}

PxRigidStatic* PhysxAgent::create_ground(vec3 scaleFactors)
{
	if (ground_mesh == NULL)
	{
		MeshData* ground_data = MeshMap::Instance()->getEntityMesh("sphere.obj");
		ground_mesh = create_convex_mesh(*ground_data->getVertices());
		ground_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	}

	PxFilterData simFilterData;
	EntityTypes type = EntityTypes::GROUND;
	simFilterData.word0 = type;
	simFilterData.word1 = collides_with(type);
	PxFilterData queryFilterData;
	queryFilterData.word3 = driveable(type);

	PxTransform transform(PxIdentity);
	PxMeshScale scale(PxVec3(scaleFactors.x, scaleFactors.y, scaleFactors.z), PxQuat(PxIdentity));

	PxRigidStatic* actor = gPhysics->createRigidStatic(transform);
	PxShape* shape = actor->createShape(PxConvexMeshGeometry(ground_mesh, scale), *ground_material);
	shape->setQueryFilterData(queryFilterData);
	shape->setSimulationFilterData(simFilterData);
	shape->setLocalPose(PxTransform(PxIdentity));
	gScene->addActor(*actor);
	return actor;
}

PxRigidStatic* PhysxAgent::create_ground_sphere(float scale_factor)
{
	if (ground_mesh == NULL)
	{
		MeshData* ground_data = MeshMap::Instance()->getEntityMesh("sphere.obj");
		ground_mesh = create_convex_mesh(*ground_data->getVertices());
		ground_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	}
	PxFilterData simFilterData;
	EntityTypes type = EntityTypes::GROUND;
	simFilterData.word0 = type;
	simFilterData.word1 = collides_with(type);
	PxFilterData queryFilterData;
	queryFilterData.word3 = driveable(type);

	PxTransform transform(PxIdentity);
	
	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, PxSphereGeometry(scale_factor), *ground_material);
	PxShape* shapes[1];
	actor->getShapes(shapes, 1);
	PxShape* shape = shapes[0];
	/*
	PxRigidStatic* actor = gPhysics->createRigidStatic(transform);
	PxShape* shape = actor->createShape(PxSphereGeometry(scale_factor), *ground_material);
	*/
	shape->setQueryFilterData(queryFilterData);
	shape->setSimulationFilterData(simFilterData);
	shape->setLocalPose(PxTransform(PxIdentity));
	gScene->addActor(*actor);
	return actor;
}

PxRigidStatic* PhysxAgent::create_ground_plane()
{
	if (ground_mesh == NULL)
	{
		MeshData* ground_data = MeshMap::Instance()->getEntityMesh("sphere.obj");
		ground_mesh = create_convex_mesh(*ground_data->getVertices());
		ground_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	}
	PxFilterData simFilterData;
	EntityTypes type = EntityTypes::GROUND;
	simFilterData.word0 = type;
	simFilterData.word1 = collides_with(type);
	PxFilterData queryFilterData;
	queryFilterData.word3 = driveable(type);

	PxTransform transform(PxVec3(PxIdentity), PxQuat(PxPiDivTwo, PxVec3(0,0,1)));

	PxRigidStatic* actor = PxCreateStatic(*gPhysics, transform, PxPlaneGeometry(), *ground_material);
	PxShape* shapes[1];
	actor->getShapes(shapes, 1);
	PxShape* shape = shapes[0];

	shape->setQueryFilterData(queryFilterData);
	shape->setSimulationFilterData(simFilterData);
	shape->setLocalPose(PxTransform(PxIdentity));
	gScene->addActor(*actor);
	return actor;
}

PxRigidActor* PhysxAgent::create_static_convex_mesh(MeshData* mesh_data, PxTransform transform, EntityTypes type)
{
	PxFilterData simFilterData;
	PxFilterData queryFilterData;
	simFilterData.word0 = type;
	simFilterData.word1 = collides_with(type);
	queryFilterData.word3 = driveable(type);

	vector<PxVec3> vertices = vector<PxVec3>();
	vector<vec3> *vecs = mesh_data->getVertices();
	for (unsigned int i=0; i<vecs->size(); i++) {
		vertices.push_back(PxVec3(vecs->at(i).x, vecs->at(i).y, vecs->at(i).z));
	}

	PxConvexMeshDesc convexDesc;
	convexDesc.points.count	= vertices.size();
	convexDesc.points.stride = sizeof(PxVec3);
	convexDesc.points.data = vertices.data();
	convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX | PxConvexFlag::eINFLATE_CONVEX;

	PxConvexMesh* convexMesh = NULL;
	PxDefaultMemoryOutputStream buf;
	if(gCooking->cookConvexMesh(convexDesc, buf))
	{
		PxDefaultMemoryInputData id(buf.getData(), buf.getSize());
		convexMesh = gPhysics->createConvexMesh(id);
	}
	PxMaterial* gMaterial = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	PxRigidStatic* actor = gPhysics->createRigidStatic(transform);
	PxShape* shape = actor->createShape(PxConvexMeshGeometry(convexMesh), *gMaterial);
	shape->setQueryFilterData(queryFilterData);
	shape->setSimulationFilterData(simFilterData);
	shape->setLocalPose(PxTransform(PxIdentity));
	return actor;
}
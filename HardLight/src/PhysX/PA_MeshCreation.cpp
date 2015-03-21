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
static PxQuat RotationBetweenVectors(PxVec3 start, PxVec3 dest)
{
	start.normalize();
	dest.normalize();

	float cosTheta = start.dot(dest);
	PxVec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = PxVec3(0.f, 0.f, 1.f).cross(start);
		if (rotationAxis.magnitude() < 0.001f) // bad luck, they were parallel, try again!
			rotationAxis = PxVec3(1.f, 0.f, 0.f).cross(start);

		rotationAxis.normalize();
		return PxQuat(PxPi, rotationAxis);
	}

	rotationAxis = start.cross(dest);

	float s = sqrt((1.f + cosTheta) * 2.f);
	float invs = 1.f / s;

	return PxQuat(
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs,
		s * 0.5f
		);
}

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
PxQuat PhysxAgent::PxLookAt(vec3 direction, vec3 up)
{
	PxVec3 d = PxVec3(direction.x, direction.y, direction.z);
	PxVec3 u = PxVec3(up.x, up.y, up.z);
	return PxLookAt(d, u);
}

PxQuat PhysxAgent::PxLookAt(PxVec3 direction, PxVec3 up)
{
	direction.normalize();
	PxVec3 right = direction.cross(up).getNormalized();
	up = right.cross(direction).getNormalized();

	PxQuat q1 = RotationBetweenVectors(PxVec3(0.f,0.f,1.f), direction).getNormalized();

	PxVec3 newUp = q1.rotate(PxVec3(0.f,1.f,0.f)).getNormalized();

	PxQuat q2 = RotationBetweenVectors(newUp, up).getNormalized();

	PxQuat q3 = q2*q1;
	return q3.getNormalized();
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

PxRigidStatic* PhysxAgent::create_wall_plane(PxPlane plane)
{
	if (wall_mesh == NULL)
	{
		MeshData* wall_data = MeshMap::Instance()->getEntityMesh("arenaWall.obj");
		wall_mesh = create_convex_mesh(*wall_data->getVertices());
		wall_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	}
	PxFilterData simFilterData;
	EntityTypes type = EntityTypes::WALL;
	simFilterData.word0 = type;
	simFilterData.word1 = collides_with(type);
	PxFilterData queryFilterData;
	queryFilterData.word3 = driveable(type);

	PxRigidStatic* actor = PxCreatePlane(*gPhysics, plane, *wall_material);
	PxShape* shapes[1];
	actor->getShapes(shapes, 1);
	PxShape* shape = shapes[0];

	shape->setQueryFilterData(queryFilterData);
	shape->setSimulationFilterData(simFilterData);
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
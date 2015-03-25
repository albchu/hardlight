#include "PhysxAgent.h"

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

PxRigidStatic* PhysxAgent::create_tail(vec3 old_location, vec3 new_location, vec3 v3up, float width, float height)
{
	if (tail_mesh == NULL)
	{
		MeshData* tail_data = MeshMap::Instance()->getEntityMesh("tail.obj");
		tail_mesh = create_convex_mesh(*tail_data->getVertices());
		tail_material = gPhysics->createMaterial(2.0f, 2.0f, 0.6f);
	}
	vec3 v3direction = normalize(old_location - new_location); // from new to old
	float distance = glm::distance(old_location, new_location);

	PxVec3 direction = PxVec3(v3direction.x, v3direction.y, v3direction.z).getNormalized();
	PxVec3 up = PxVec3(v3up.x, v3up.y, v3up.z).getNormalized();
	PxVec3 right = up.cross(direction).getNormalized();
	direction = right.cross(up).getNormalized();

	PxTransform transform(PxVec3(new_location.x, new_location.y, new_location.z), PxLookAt(direction, up));
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
		MeshData* pickup_data = MeshMap::Instance()->getEntityMesh("powerup_random.obj");
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
	PxMeshScale scale(PxVec3(scaleFactors.x + 2, scaleFactors.y + 2, scaleFactors.z + 2), PxQuat(PxIdentity));	// Plus 2 to make the collision box a little easier to hit 

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
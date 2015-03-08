#include "PhysxAgent.h"

PxRigidActor* PhysxAgent::create_static_convex_mesh(MeshData* mesh_data, PxTransform transform, EntityTypes type)
{
	PxFilterData simFilterData;
	PxFilterData queryFilterData;
	simFilterData.word0 = type;
	switch (type) // COLLIDES_WITH
	{
	case WALL:
		queryFilterData.word3 = UNDRIVABLE_SURFACE;
		simFilterData.word1 = BIKE;
		break;
	case BIKE:
		queryFilterData.word3 = UNDRIVABLE_SURFACE;
		simFilterData.word1 = WALL | BIKE | GROUND | TAIL_SEGMENT | PICKUP;
		break;
	case GROUND:
		queryFilterData.word3 = DRIVABLE_SURFACE;
		simFilterData.word1 = BIKE;
		break;
	case TAIL_SEGMENT:
		queryFilterData.word3 = UNDRIVABLE_SURFACE;
		simFilterData.word1 = BIKE;
		break;
	case PICKUP:
		queryFilterData.word3 = UNDRIVABLE_SURFACE;
		simFilterData.word1 = BIKE;
		break;
	default:
		queryFilterData.word3 = UNDRIVABLE_SURFACE;
		simFilterData.word1 = 0;
		break;
	}

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
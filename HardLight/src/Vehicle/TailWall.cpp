#include "Vehicle/TailWall.h"
#include "../inih/cpp/INIReader.h"
#include "../SnippetVehicleCommon/SnippetVehicleCreate.h"

TailWall::TailWall(Bike* new_bike, INIReader* new_config)
{
	config = new_config;		// Needed to be passed into tail segments
	max_length = config->GetInteger("tail", "maxLength", 30);
	min_segment_allowance = (float)config->GetReal("tail", "minSegmentSize", 0.5);
	max_segment_allowance = (float)config->GetReal("tail", "maxSegmentSize", 100);
	tail_offset_scalar = (float)config->GetReal("tail", "offset", 4);
	bike = new_bike;
	//gPose = bike->get_actor()->getGlobalPose();
	//last_position = vec3(gPose.p.x, gPose.p.y, gPose.p.z);
	last_position = getTailPosition();

}
void TailWall::update(PhysxAgent* pxAgent)
{
	vec3 new_position = getTailPosition();
	// Check the size of the tail list whether to add a new segment or reshuffle segments
	if(segments.size() >= max_length)
	{
		// Reshuffle segments
		TailSegment* segment = segments[segments.size()-1];
		segment->get_actor()->release();
		segments.pop_back();
	}
	// Create a new wall segment if the wall segment is at least a certain length
	float length = glm::distance(new_position, last_position);
	if(length >= min_segment_allowance && length <= max_segment_allowance )
	{
		PxRigidActor* segment_actor = pxAgent->get_physics()->createRigidStatic(getTailTransform());
		TailSegment* segment = new TailSegment(new_position, last_position, segment_actor, "../data/Textures/LightTrail.tga", config);
		segments.insert(segments.begin(), segment);
		float width = (float)config->GetReal("tail", "width", 100);
		float height = (float)config->GetReal("tail", "height", 100);
		// Cook the wall mesh generated for this segment
		PxConvexMesh* chassisConvexMesh = createChassisMesh(PxVec3(width, height, length), *pxAgent->get_physics(), *pxAgent->get_cooking());
		PxMaterial* wall_material = pxAgent->get_physics()->createMaterial(2.0f, 2.0f, 0.6f);
		PxShape* shape = segment->get_actor()->createShape(PxConvexMeshGeometry(chassisConvexMesh), *wall_material);
		
		//attachShape(*shape);
		//shape->release();

		// Set up sim data for tail segment
		PxFilterData simFilterData;
		PxFilterData qryFilterData;
		qryFilterData.word3 = (PxU32)UNDRIVABLE_SURFACE;
		simFilterData.word0 = COLLISION_FLAG_OBSTACLE;
		simFilterData.word1 = COLLISION_FLAG_OBSTACLE_AGAINST;
		shape->setQueryFilterData(qryFilterData);
		shape->setSimulationFilterData(simFilterData);
		pxAgent->get_scene()->addActor(*segment->get_actor());
		if(length >= min_segment_allowance)
		{
			last_position = new_position;	// Update last set position for next wall segment
		}
	}
}

// Returns the pxTransform of the tail with appropriate physx transform offsets
PxTransform TailWall::getTailTransform()
{
	// Update segment actor position
	vec3 location = bike->get_location();
	vec3 direction = bike->get_direction_vector();

	// Get a point that moves behind the direction vector
	location = location - (direction * vec3(tail_offset_scalar,tail_offset_scalar,tail_offset_scalar));

	// Offset the physx actor for the tail so it doesnt start in the exact same spot as its bike
	PxTransform bikeTransform = PxTransform(location.x, location.y, location.z, bike->get_actor()->getGlobalPose().q);

	return bikeTransform;
}

// Returns the pxTransform of the tail with appropriate physx transform offsets
vec3 TailWall::getTailPosition()
{
	// Update segment actor position
	vec3 location = bike->get_location();
	vec3 direction = bike->get_direction_vector();

	// Get a point that moves behind the direction vector
	return location - (direction * vec3(tail_offset_scalar,tail_offset_scalar,tail_offset_scalar));
}

void TailWall::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	for (TailSegment* segment : segments)
	{
		segment->render(projection_matrix, view_matrix, lightPos);
	}
}

Bike* TailWall::getBike()
{
	return bike;
}

void TailWall::extend_max_length()
{
	max_length += max_length;
}

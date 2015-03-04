#include "Vehicle/TailWall.h"

TailWall::TailWall(Bike* new_bike)
{
	max_length = 60;
	min_segment_allowance = 0.005f;
	max_segment_allowance = 1000.0f;
	tail_offset_scalar = 4;
	bike = new_bike;
	gPose = bike->get_actor()->getGlobalPose();
	last_position = vec3(gPose.p.x, gPose.p.y, gPose.p.z);

}

void TailWall::update(PxScene* gScene, PxPhysics* gPhysics)
{
	vec3 new_position = bike->get_location();
	// Check the size of the tail list whether to add a new segment or reshuffle segments
	if(segments.size() >= max_length)
	{
		// Reshuffle segments
		TailSegment* segment = segments[segments.size()-1];
		segments.pop_back();
		segments.insert(segments.begin(), segment);
		segment->get_actor()->setGlobalPose(getTailTransform());
	}
	else
	{
		// Check that the wall segment is at least a certain length
		float distance = glm::distance(new_position, last_position);
		if(distance >= min_segment_allowance && distance <= max_segment_allowance )
		{
			PxRigidActor* segment_actor = gPhysics->createRigidStatic(getTailTransform());
			TailSegment* segment = new TailSegment(new_position, last_position, segment_actor, "../data/Textures/LightTrail.tga");
			segments.insert(segments.begin(), segment);
		}
		if(distance >= min_segment_allowance)
		{
			last_position = new_position;	// Update last set position for next wall segment
		}
	}
}

// Returns the pxTransform of the tail with appropriate physx transform offsets
PxTransform TailWall::getTailTransform()
{
	// Update segment actor position
	gPose = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();		// Get latest bike position
	vec3 location = bike->get_location();
	vec3 direction = bike->get_direction_vector();

	// Get a point that moves behind the direction vector
	location = location - (direction * vec3(tail_offset_scalar,tail_offset_scalar,tail_offset_scalar));


	// Offset the physx actor for the tail so it doesnt start in the exact same spot as its bike
	PxTransform bikeTransform = PxTransform(location.x, location.y, location.z, gPose.q);



	return bikeTransform;
}

void TailWall::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	for (TailSegment* segment : segments)
	{
		segment->render(projection_matrix, view_matrix, lightPos);
	}
}

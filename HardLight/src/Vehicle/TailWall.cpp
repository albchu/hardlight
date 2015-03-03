#include "Vehicle/TailWall.h"

TailWall::TailWall(Bike* new_bike)
{
	max_length = 60;
	min_segment_allowance = 0.05f;
	max_segment_allowance = 1000.0f;
	last_position = vec3(gPose.p.x, gPose.p.y, gPose.p.z);
	bike = new_bike;
	gPose = bike->get_actor()->getGlobalPose();
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

		// Update segment actor position
		segment->get_actor()->setGlobalPose(bike->get_actor()->getGlobalPose());
	}
	else
	{
		// Check that the wall segment is at least a certain length
		float distance = glm::distance(new_position, last_position);
		if(distance >= min_segment_allowance && distance <= max_segment_allowance )
		{
			// Add new segment to tail
			gPose = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
			PxRigidActor* segment_actor = gPhysics->createRigidStatic(PxTransform(gPose.p.x, gPose.p.y, gPose.p.z));
			TailSegment* segment = new TailSegment(new_position, last_position, segment_actor, "../data/Textures/LightTrail.tga");
			segments.insert(segments.begin(), segment);
		}
		if(distance >= min_segment_allowance)
		{
			last_position = new_position;	// Update last set position for next wall segment
		}
	}
}

void TailWall::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	for (TailSegment* segment : segments)
	{
		segment->render(projection_matrix, view_matrix, lightPos);
	}
}

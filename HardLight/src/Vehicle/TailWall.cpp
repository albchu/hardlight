#include "Vehicle/TailWall.h"

TailWall::TailWall(Bike* new_bike)
{
	max_length = 15;
	min_segment_allowance = 1.5f;
	max_segment_allowance = 1000.0f;
	tail_offset_scalar = 3;
	bike = new_bike;
	//gPose = bike->get_actor()->getGlobalPose();
	//last_position = vec3(gPose.p.x, gPose.p.y, gPose.p.z);
	last_position = getTailPosition();

}

void TailWall::update(PxScene* gScene, PxPhysics* gPhysics)
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
	float distance = glm::distance(new_position, last_position);
	if(distance >= min_segment_allowance && distance <= max_segment_allowance )
	{
		PxRigidActor* segment_actor = gPhysics->createRigidStatic(getTailTransform());
		TailSegment* segment = new TailSegment(new_position, last_position, segment_actor, TextureMap::Instance()->getTexture("../data/Textures/LightTrail.tga"));
		segments.insert(segments.begin(), segment);

		// Set up sim data for tail segment

		//PxFilterData simFilterData;
		////simFilterData.word3 = (PxU32)UNDRIVABLE_SURFACE;
		//simFilterData.word0 = COLLISION_FLAG_OBSTACLE;
		//simFilterData.word1 = COLLISION_FLAG_OBSTACLE_AGAINST;

		//cout << segment_actor->getNbShapes() << endl;
		//PxShape* shapes[1];
		//segment_actor->getShapes(shapes, 1);

		//for (PxShape* shape : segment_actor->getShapes())
		//{
		//	//shape->setQueryFilterData(qryFilterData);
		//	shape->setSimulationFilterData(simFilterData);
		//}

		//}
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

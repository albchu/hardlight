#include "Vehicle/TailWall.h"

TailWall::TailWall(Bike* new_bike)
{
	max_length = 30;
	min_segment_allowance = 2.0f;
	gPose = actor->getGlobalPose();
	last_position = vec3(gPose.p.x, gPose.p.y, gPose.p.z);
	bike = new_bike;
}

void TailWall::update(PxScene* gScene, PxPhysics* gPhysics)
{
	vec3 new_position = bike->get_location();
	// Check the size of the tail list whether to add a new segment or reshuffle segments
	if(segments.size() >= max_length)
	{
		// Reshuffle segments
		//MAGICAL CODE
	}
	else
	{
		// Check that the wall segment is at least a certain length
		float distance = glm::distance(new_position, last_position);
		if(distance >= min_segment_allowance)
		{
			// Add new segment to tail
			gPose = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
			PxRigidActor* segment_actor = gPhysics->createRigidStatic(PxTransform(gPose.p.x, gPose.p.y, gPose.p.z));
			TailSegment* segment = new TailSegment(new_position, last_position, segment_actor, "../data/Textures/LightTrail.tga");
			segments.insert(segments.begin(), segment);
			last_position = new_position;	// Update last set position for next wall segment
		}
	}
}

void TailWall::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	cout << "TAILWALL RENDER!" << endl;
	for (TailSegment* segment : segments)
	{
		segment->render(projection_matrix, view_matrix, lightPos);
	}
}

mat4 TailWall::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	//PxTransform gPose = actor->getGlobalPose();
	//model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	//PxReal rads;
	//PxVec3 axis;
	//gPose.q.toRadiansAndUnitAxis(rads, axis);
	//float scaleFactor = 3.0f;

	//model_matrix = scale(model_matrix, vec3(scaleFactor, scaleFactor, scaleFactor));

	//model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));

	return model_matrix;
}

//
//TailSegment* TailWall::addSegment(TailSegment* tail){
//	bikeWall.insert(bikeWall.begin(),tail);
//	if(bikeWall.size() > max_length){
//		tail = bikeWall.back();
//		bikeWall.pop_back();
//		return tail;
//	}
//	return NULL;
//}
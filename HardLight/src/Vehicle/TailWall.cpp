#include "Vehicle/TailWall.h"
#include "../inih/cpp/INIReader.h"
#include "../SnippetVehicleCommon/SnippetVehicleCreate.h"

TailWall::TailWall(Chassis* new_bike, INIReader* new_config)
{
	config = new_config;		// Needed to be passed into tail segments
	max_length = config->GetInteger("tail", "maxLength", 30);
	extend_length = config->GetInteger("tail", "extend_length", 10);
	min_segment_allowance = (float)config->GetReal("tail", "minSegmentSize", 0.5);
	max_segment_allowance = (float)config->GetReal("tail", "maxSegmentSize", 100);
	tail_offset_scalar = (float)config->GetReal("tail", "offset", 4);
	bike = new_bike;
	last_position = getTailPosition();
	width = (float)config->GetReal("tail", "width", 1);
	height = (float)config->GetReal("tail", "height", 1);

	// Create and compile our GLSL program from the shaders
	program_id = LoadShaders("basic_vs.glsl", "basic_fs.glsl");

}
void TailWall::update(PhysxAgent* pxAgent)
{
	// Check the size of the tail list whether to add a new segment or reshuffle segments
	while (segments.size() > max_length)
	{
		// Reshuffle segments
		TailSegment* segment = segments[segments.size()-1];
		segments.pop_back();
		PxRigidActor* actor = segment->get_actor();
		pxAgent->get_scene()->removeActor(*actor);
		actor->release();
		delete segment;
	}
	
	vec3 new_position = getTailPosition();
	float length = glm::distance(new_position, last_position);
	if (length < min_segment_allowance)
		return;

	if (max_length > 0)
	{
		PxRigidActor* segment_actor = pxAgent->create_tail(new_position, last_position, PhysxAgent::toVec3(bike->get_gravity_up()), width, height);
		TailSegment* segment = new TailSegment(segment_actor, "../data/Textures/LightTrail.tga", width, height, length, program_id);
		segments.insert(segments.begin(), segment);

		last_position = new_position;	// Update last set position for next wall segment
	}
}

// Returns the pxTransform of the tail with appropriate physx transform offsets
vec3 TailWall::getTailPosition()
{
	// Update segment actor position
	vec3 location = bike->get_location();
	vec3 direction = bike->get_direction_vector();

	// Get a point that moves behind the direction vector
	return location - (direction * tail_offset_scalar);
}

void TailWall::render(mat4 projection_matrix, mat4 view_matrix, vec3 lightPos)
{
	for (TailSegment* segment : segments)
	{
		segment->render(projection_matrix, view_matrix, lightPos);
	}
}

Chassis* TailWall::getBike()
{
	return bike;
}

void TailWall::extend_max_length()
{
	max_length += extend_length;
}

void TailWall::set_max_length(int new_length)
{
	max_length = new_length;
}
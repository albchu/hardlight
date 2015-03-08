#include "Vehicle/TailSegment.h"

// Takes two positions, start (closer to bike), and end (farther from bike)
TailSegment::TailSegment(vec3 new_start, vec3 new_end, PxRigidActor* init_actor, const char * texturePath, INIReader* config)
{
	start = new_start;
	end = new_end;

	width = (float)config->GetReal("tail", "width", 100);
	height = (float)config->GetReal("tail", "height", 100);
	type = TAIL_SEGMENT;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	mesh_data = new MeshData();
	generate_wall_mesh();

	texture = TextureMap::Instance()->getTexture("../data/Textures/LightTrail.tga");
	init_opengl();
	deleted = false;
}

// Generates a renderable mesh using the starting and ending positions
void TailSegment::generate_wall_mesh()
{
	vec3 tail_vector = normalize(end - start); // Get a vector from the start of the tail seg to the end
	vec3 global_up = vec3(0,1,0);
	vec3 perp_vector = normalize(cross(tail_vector, global_up));    // Get perpendicular vector for calculating wideness of wall

	// These two are used for calculating the actual mesh points
	vec3 start_top = vec3(start.x, start.y + height, start.z);
	vec3 end_top = vec3(end.x, end.y + height, end.z);

	// Calculate the mesh points
	vec3 start_bottom_left = start - ((width/2) * perp_vector);
	vec3 start_bottom_right = start + ((width/2) * perp_vector);

	vec3 start_top_left = start_top - ((width/2) * perp_vector);
	vec3 start_top_right = start_top + ((width/2) * perp_vector);

	vec3 end_bottom_left = end - ((width/2) * perp_vector);
	vec3 end_bottom_right = end + ((width/2) * perp_vector);

	vec3 end_top_left = end_top - ((width/2) * perp_vector);
	vec3 end_top_right = end_top + ((width/2) * perp_vector);

	mesh_data->addVertex(start_bottom_left);	// Index: 0
	mesh_data->addVertex(start_bottom_right);	// Index: 1
	mesh_data->addVertex(start_top_left);		// Index: 2
	mesh_data->addVertex(start_top_right);		// Index: 3
	mesh_data->addVertex(end_bottom_left);		// Index: 4
	mesh_data->addVertex(end_bottom_right);		// Index: 5
	mesh_data->addVertex(end_top_left);			// Index: 6
	mesh_data->addVertex(end_top_right);		// Index: 7

	mesh_data->addTexture(vec2(0.0f, 0.0f));
	mesh_data->addTexture(vec2(1.0f, 0.0f));
	mesh_data->addTexture(vec2(0.0f, 1.0f));
	mesh_data->addTexture(vec2(1.0f, 1.0f));

	mesh_data->addNormal(perp_vector);
	mesh_data->addNormal(perp_vector*-1.0f);
	mesh_data->addNormal(global_up * -1.0f);
	
	// Left face
	mesh_data->addFace(vec3(0,2,4)); mesh_data->addFaceTexture(vec3(0,2,1)); mesh_data->addFaceNormal(vec3(1,1,1));
	mesh_data->addFace(vec3(6,4,2)); mesh_data->addFaceTexture(vec3(0,2,1)); mesh_data->addFaceNormal(vec3(1,1,1));

	// Right face
	mesh_data->addFace(vec3(1,5,3)); mesh_data->addFaceTexture(vec3(0,1,2)); mesh_data->addFaceNormal(vec3(0,0,0));
	mesh_data->addFace(vec3(7,3,5)); mesh_data->addFaceTexture(vec3(0,1,2)); mesh_data->addFaceNormal(vec3(0,0,0));

	// Top face
	mesh_data->addFace(vec3(2,3,6)); mesh_data->addFaceTexture(vec3(0,2,1)); mesh_data->addFaceNormal(vec3(2,2,2));
	mesh_data->addFace(vec3(7,6,3)); mesh_data->addFaceTexture(vec3(0,2,1)); mesh_data->addFaceNormal(vec3(2,2,2));

	mesh_data->order_arrays();
}

mat4 TailSegment::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	//PxTransform gPose = actor->getGlobalPose();

	//model_matrix = translate(model_matrix, vec3(0, -1, 0));

	//PxReal rads;
	//PxVec3 axis;
	//gPose.q.toRadiansAndUnitAxis(rads, axis);

	////model_matrix = scale(model_matrix, vec3(2,1,0.5));
	//model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));       // Flip the model to get the correct physx bike lean
	//model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));

	return model_matrix;
}

void TailSegment::set_start(vec3 new_start)
{
	start = new_start;
}

void TailSegment::set_end(vec3 new_end)
{
	end = new_end;
}

vec3 TailSegment::get_start()
{
	return start;
}

vec3 TailSegment::get_end()
{
	return end;
}

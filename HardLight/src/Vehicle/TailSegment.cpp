#include "Vehicle/TailSegment.h"

// Takes two positions, start (closer to bike), and end (farther from bike)
TailSegment::TailSegment(vec3 new_start, vec3 new_end, PxRigidActor* init_actor, const char* texture_file_path)
{
	start = new_start;
	end = new_end;
	type = TAIL_SEGMENT;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	generate_wall_mesh();
	mesh_data = MeshMap::Instance()->getEntityMesh("Wall.obj");
	
	//mesh_data = new MeshData();
	//mesh_data->setVertices(mesh);
	texture = load_tga_texture(texture_file_path);
	init_opengl();
	deleted = false;
}

// Generates a renderable mesh using the starting and ending positions
void TailSegment::generate_wall_mesh()
{
	vec3 tail_vector = normalize(end - start); // Get a vector from the start of the tail seg to the end
	vec3 global_up = vec3(0,1,0);
	vec3 perp_vector = cross(tail_vector, global_up);	// Get perpendicular vector for calculating wideness of wall

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

	mesh.push_back(start_bottom_left);
	mesh.push_back(end_bottom_left);
	mesh.push_back(start_top_left);
	
	mesh.push_back(end_top_left);
	mesh.push_back(start_bottom_left);
	mesh.push_back(start_top_left);

	mesh.push_back(start_bottom_right);
	mesh.push_back(end_bottom_right);
	mesh.push_back(start_top_right);

	mesh.push_back(end_top_right);
	mesh.push_back(start_bottom_right);
	mesh.push_back(start_top_right);
}

mat4 TailSegment::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	
	//model_matrix = scale(model_matrix, vec3(2,1,0.5));
	model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));	// Flip the model to get the correct physx bike lean
	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
	
	return model_matrix;
}




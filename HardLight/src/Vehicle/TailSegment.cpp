#include "Vehicle/TailSegment.h"

//TailSegment::TailSegment()
//{
//	tailScale = 1.0f;
//}

// Takes two positions, start (closer to bike), and end (farther from bike)
TailSegment::TailSegment(vec3 new_start, vec3 new_end, PxRigidActor* init_actor, const char* texture_file_path)
{
	start = new_start;
	end = new_end;
	type = TAIL_SEGMENT;
	draw_mode = GL_TRIANGLES;
	actor = init_actor;
	
	generate_wall_mesh();
	mesh_data = new MeshData();
	mesh_data->setVertices(mesh);
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

/*
void TailSegment::CreateTail(vec3 topLeft, vec3 topRight, float height)
{
	vec3 wallNormal;
	vec3 cross1, cross2;
	//top half of wall
	mesh_data->addVertex(topLeft);
	mesh_data->addVertex(vec3(topLeft.x,topLeft.y-height,topLeft.z));
	mesh_data->addVertex(topRight);
	cross1 = vec3(topLeft.x,topLeft.y-height,topLeft.z)-topLeft;
	cross2 =topRight-topLeft;
	wallNormal = cross(cross1,cross2);
	normalize(wallNormal);
	//bottom half of wall
	mesh_data->addVertex(vec3(topLeft.x,topLeft.y-height,topLeft.z));
	mesh_data->addVertex(topRight);
	mesh_data->addVertex(vec3(topRight.x,topRight.y-height,topRight.z));

	for(int i = 0; i<6;i++){
		mesh_data->addNormal(wallNormal);
	}

	mesh_data->addTexture(vec2(0,0));
	mesh_data->addTexture(vec2(0,1));
	mesh_data->addTexture(vec2(1,0));
	mesh_data->addTexture(vec2(0,1));
	mesh_data->addTexture(vec2(1,0));
	mesh_data->addTexture(vec2(1,1));
}*/
//
//mat4 TailSegment::get_model_matrix()
//{
//	mat4 model_matrix = mat4(1.0);
//	PxTransform gPose = actor->getGlobalPose();
//	
//	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
//	
//	PxReal rads;
//	PxVec3 axis;
//	gPose.q.toRadiansAndUnitAxis(rads, axis);
//	
//	model_matrix = scale(model_matrix, vec3(2.5, 2.5, 2.5));
//	model_matrix = scale(model_matrix, vec3(tailScale/2, 1, tailScale/2));
//	model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));	// Flip the bike model around: This is a hack to get the correct physx bike lean
//	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
//	
//	model_matrix = translate(model_matrix, vec3(0, 0, (1.5+tailScale)/(tailScale)));
//
//	return model_matrix;
//}
//void TailSegment::setScale(float size){
//	tailScale = size;
//}
//
//

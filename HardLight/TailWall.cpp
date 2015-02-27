#include "TailWall.h"

TailWall::TailWall()
{
	mesh_data = new MeshData();
}

void TailWall::CreateTail(vec3 topLeft, vec3 topRight, float height)
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
}

mat4 TailWall::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	
	model_matrix = scale(model_matrix, vec3(2.5, 2.5, 2.5));
	model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));	// Flip the bike model around: This is a hack to get the correct physx bike lean

	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
	model_matrix = translate(model_matrix, vec3(0, 0, 1.5));

	return model_matrix;
}

vector<vec3> TailWall::getTail(void)
{
	return Tails;
}
vector<vec2> TailWall::getTailUV(){
	return TailUV;
}
vector<vec3> TailWall::getTailNorm(){
	return Normals;
}


#include "Bike.h"

mat4 Bike::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	
	//	std::cout << "\nRotation degrees: " << rads * 180/PxPi << endl;
	//	std::cout << "Rotation axis: " << glm::to_string(vec3(axis.x, axis.y, axis.z)) << endl;
	model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));
	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
	//model_matrix = rotate(model_matrix, rads, vec3(0, 0, axis.z));
	//model_matrix = rotate(model_matrix, rads, vec3(0, axis.y, 0));
	//model_matrix = rotate(model_matrix, rads, vec3(axis.x, 0, 0));
	//model_matrix = scale(model_matrix, vec3(2.5,2.5,2.5));

	return model_matrix;
}

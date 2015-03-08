#include "Vehicle/Bike.h"

Bike::Bike()
{
	type = BIKE;
	draw_mode = GL_TRIANGLES;
	mesh_data = MeshMap::Instance()->getEntityMesh("HardLightBike2.obj");
	invincible = false;
	deleted = false;
}

Bike::~Bike() {
}

mat4 Bike::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	//cout << "Bike location" << glm::to_string(vec3(gPose.p.x, gPose.p.y, gPose.p.z)) << endl;
	model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));	// Flip the bike model around: This is a hack to get the correct physx bike lean
	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
	//model_matrix = rotate(model_matrix, rads * (axis.x), vec3(1, 0, 0));
	//model_matrix = rotate(model_matrix, rads * (axis.y), vec3(0, 1, 0));
	//model_matrix = rotate(model_matrix, (rads * normalize(axis.z)) * -5.0f, vec3(0, 0, 1));

	//model_matrix = scale(model_matrix, vec3(2.5,2.5,2.5));

	return model_matrix;
}

PxVehicleDrive4W* Bike::getVehicle4W()
{
	return vehicle4W;
}

PxVehicleDrive4WRawInputData& Bike::getInputData()
{
	return inputData;
}

VehicleSceneQueryData* Bike::getVehicleSceneQueryData()
{
	return vehicleSceneQueryData;
}

PxBatchQuery* Bike::getBatchQuery()
{
	return batchQuery;
}

bool Bike::isInAir()
{
	return inAir;
}

void Bike::setVehicle4W(PxVehicleDrive4W* new_vehicle4W)
{
	vehicle4W = new_vehicle4W;
}


void Bike::setInputData(PxVehicleDrive4WRawInputData new_inputData)
{
	inputData = new_inputData;
}


void Bike::setVehicleSceneQueryData(VehicleSceneQueryData* new_vehicleSceneQueryData)
{
	vehicleSceneQueryData = new_vehicleSceneQueryData;
}


void Bike::setBatchQuery(PxBatchQuery* new_batchQuery)
{
	batchQuery = new_batchQuery;
}


void Bike::setInAir(bool new_inAir)
{
	inAir = new_inAir;
}

//TailWall* Bike::get_tail_wall()
//{
//	return tail_wall;
//}

void Bike::set_actor(PxRigidActor* new_actor)
{
	actor = new_actor;
	PxTransform gPose = actor->getGlobalPose();
	//tail_wall = new TailWall(vec3(gPose.p.x, gPose.p.y, gPose.p.z), this);	// Initialize the tail object as soon as an actor is set for the bike;
}

void Bike::adaptiveSteering(int analogStickInput)
{
	//float currentSpeed = 0.0f; // Maybe custom type, int, double
	//// Get bikes current speed
	//// Get max speed
	//// currentSpeed /= maxSpeed
	//currentSpeed = 1 - currentSpeed; // (1-x)
	//currentSpeed = pow(currentSpeed, 3.0f); // (1-x)^3
	//inputData.setAnalogSteer((currentSpeed)*(analogStickInput)/(-32768.0f)); //the axis are inverted on the controller
	inputData.setAnalogSteer((analogStickInput)/(-32768.0f)); //the axis are inverted on the controller

}
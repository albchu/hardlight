#include "Vehicle/Chassis.h"

Chassis::Chassis()
{
	type = UNDECLARED;
	draw_mode = GL_TRIANGLES;
	mesh_data = MeshMap::Instance()->getEntityMesh("HardLightBike2.obj");
	invincible = false;
	renderable = true;
	previousAnalogStickInput = 0;
	steeringParameter = 0.0f;
}

Chassis::~Chassis() {
}

mat4 Chassis::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	//cout << "Chassis location" << glm::to_string(vec3(gPose.p.x, gPose.p.y, gPose.p.z)) << endl;
	model_matrix = rotate(model_matrix, PxPi, vec3(0, 1, 0));	// Flip the bike model around: This is a hack to get the correct physx bike lean
	model_matrix = rotate(model_matrix, rads, vec3(axis.x, axis.y, axis.z));
	//model_matrix = rotate(model_matrix, rads * (axis.x), vec3(1, 0, 0));
	//model_matrix = rotate(model_matrix, rads * (axis.y), vec3(0, 1, 0));
	//model_matrix = rotate(model_matrix, (rads * normalize(axis.z)) * -5.0f, vec3(0, 0, 1));

	//model_matrix = scale(model_matrix, vec3(2.5,2.5,2.5));

	return model_matrix;
}

PxVehicleDrive4W* Chassis::getVehicle4W()
{
	return vehicle4W;
}

PxVehicleDrive4WRawInputData& Chassis::getInputData()
{
	return inputData;
}

VehicleSceneQueryData* Chassis::getVehicleSceneQueryData()
{
	return vehicleSceneQueryData;
}

PxBatchQuery* Chassis::getBatchQuery()
{
	return batchQuery;
}

bool Chassis::isInAir()
{
	return inAir;
}

void Chassis::setVehicle4W(PxVehicleDrive4W* new_vehicle4W)
{
	vehicle4W = new_vehicle4W;
}


void Chassis::setInputData(PxVehicleDrive4WRawInputData new_inputData)
{
	inputData = new_inputData;
}


void Chassis::setVehicleSceneQueryData(VehicleSceneQueryData* new_vehicleSceneQueryData)
{
	vehicleSceneQueryData = new_vehicleSceneQueryData;
}


void Chassis::setBatchQuery(PxBatchQuery* new_batchQuery)
{
	batchQuery = new_batchQuery;
}


void Chassis::setInAir(bool new_inAir)
{
	inAir = new_inAir;
}

//TailWall* Chassis::get_tail_wall()
//{
//	return tail_wall;
//}

void Chassis::set_actor(PxRigidActor* new_actor)
{
	actor = new_actor;
	PxTransform gPose = actor->getGlobalPose();
	//tail_wall = new TailWall(vec3(gPose.p.x, gPose.p.y, gPose.p.z), this);	// Initialize the tail object as soon as an actor is set for the bike;
}

void Chassis::adaptiveSteering(int analogStickInput)
{
	//cout << "========INPUT========" << endl;
	//cout << "analogStickInput" << analogStickInput << endl;
	//cout << "previousAnalogStickInput" << previousAnalogStickInput << endl;
	//int direction = 0;
	//int difference = analogStickInput - previousAnalogStickInput;
	//cout << "difference" << difference << endl;
	//if(difference != 0)
	//{
	//	if(difference > 0)
	//	{
	//		direction = 1;
	//	}
	//	else
	//	{
	//		direction = -1;
	//	}
	//}
	//else
	//{
	//	direction = 0;
	//}
	//
	//steeringParameter = steeringParameter + (float)direction * 0.01f;
	//if(abs(steeringParameter) > 1.0f)
	//{
	//	if(direction > 0)
	//	{
	//		steeringParameter = 1.0f;
	//	}
	//	else
	//	{
	//		steeringParameter = -1.0f;
	//	}
	//}
	//cout << steeringParameter << endl;
	//inputData.setAnalogSteer(-steeringParameter);


	//cout << "direction" << direction << endl;
	//if(abs(difference) > 2048) 
	//{
	//	previousAnalogStickInput = previousAnalogStickInput+direction*1028;
	//}
	//else
	//	previousAnalogStickInput = analogStickInput;
	//cout << "previousAnalogStickInput" << previousAnalogStickInput << endl;
	//cout << (previousAnalogStickInput)/(-32768.0f) << endl;


	////float currentSpeed = 0.0f; // Maybe custom type, int, double
	////// Get bike_manager current speed
	//PxVec3 temp = vehicle4W->getRigidDynamicActor()->getLinearVelocity();
	////std::cout << "Linear Velocity: " << temp.x << " " << temp.y << " " << temp.z << " " << std::endl;
	//float currentSpeed = temp.magnitude();
	//printf("Speed: %f\n", currentSpeed);
	//// Get max speed
	//float maxSpeed = 75.0f;
	//if(currentSpeed > maxSpeed)
	//	currentSpeed = maxSpeed;
	//// currentSpeed /= maxSpeed
	//currentSpeed /= maxSpeed;
	//currentSpeed = 1.0f - currentSpeed / 2.0f; // (1-x)
	//currentSpeed = pow(currentSpeed, 3.0f); // (1-x)^3
	//inputData.setAnalogSteer((currentSpeed)*(analogStickInput)/(-32768.0f)); //the axis are inverted on the controller
	
	inputData.setAnalogSteer((analogStickInput)/(-32768.0f)); //the axis are inverted on the controller
}

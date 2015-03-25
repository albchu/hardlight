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

mat4 Chassis::get_model_matrix()
{
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);

	glm::quat rot(gPose.q.w, gPose.q.x, gPose.q.y, gPose.q.z);
	glm::vec3 rot_euler_angles = glm::eulerAngles(rot);

	float radsx = rot_euler_angles.x;
	float radsy = rot_euler_angles.y;
	float radsz = rot_euler_angles.z;

	//Correct's bike lean. KEVIN PLEASE DO NOT REMOVE THESE LINES IN CASE WE DECIDE NOT TO USE SPHERE. THEY WORK FOR PLANE.
	// Please talk to albert before this block is changed
	radsx =  (2 * PxPi - rot_euler_angles.x);
	radsz = (2 * PxPi - rot_euler_angles.z);

	model_matrix = rotate(model_matrix, radsz, vec3(0, 0, 1));
	model_matrix = rotate(model_matrix, radsy, vec3(0, 1, 0));
	model_matrix = rotate(model_matrix, radsx, vec3(1, 0, 0));

	model_matrix = scale(model_matrix, vec3(2.5,2.5,2.5));

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

void Chassis::set_actor(PxRigidActor* new_actor)
{
	actor = new_actor;
}

bool Chassis::is_invincible()
{
	return invincible;
}

void Chassis::set_invincible(bool new_invincible)
{
	invincible = new_invincible;
}

void Chassis::toggle_invincible()
{
	invincible = !invincible;
}

void Chassis::set_gravity_up(PxVec3 new_gravity)
{
	gravity_up = new_gravity.getNormalized();
}

PxVec3 Chassis::get_gravity_up()
{
	return gravity_up;
}

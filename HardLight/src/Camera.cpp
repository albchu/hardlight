#include "Camera.h"

Camera::Camera( INIReader* init_config, PxRigidActor* init_focalTarget) {

	config = init_config;
	projection_matrix = perspective(
		(float)config->GetReal("camera", "fov", 60.0)/180.0f*PxPi,
		(float)config->GetInteger("window", "width", 800)/(float)config->GetInteger("window", "height", 600),
		0.1f, 10000.0f);

	cam_translate = vec3(
		(float)config->GetReal("camera", "x", 0.0),
		(float)config->GetReal("camera", "y", 5.0),
		(float)config->GetReal("camera", "z", -10.0));
	cam_rotate = 0.0f;
	global_up = vec3(0.0f,1.0f,0.0f);
	focalTarget = init_focalTarget;		// This is what the camera will be tracking
}

// Moves the camera forward and back
void Camera::update_translationZ(float translation)
{
	cam_translate += vec3(0.0f, 0.0f, translation);
}

void Camera::update_rotation(float rads)
{
	cam_rotate += rads / 30.0f;	// Slow it down by div by some number, currently 30

	// Clamp the value to somewhere in a valid range
	if (cam_rotate > PxTwoPi) cam_rotate -= PxTwoPi;
	if (cam_rotate < 0.0f) cam_rotate += PxTwoPi;
}

// Performs all camera updates and preps the view matrix with the appropriate calculations
void Camera::update(float translationZ, float rotationRads)
{
	update_translationZ(translationZ);
	update_rotation(rotationRads);

	// Set up the camera's position
	camera_position = cam_translate;	// Set the initial camera position 
	camera_position = rotateY(camera_position, cam_rotate); // If there was any rotation, we need to take that into account for position as well

	// This will rotate the camera so that it is always rotating relative to the focal target
	PxTransform target_pose = focalTarget->getGlobalPose();
	PxReal rads;
	PxVec3 axis;
	target_pose.q.toRadiansAndUnitAxis(rads, axis);
	camera_position = rotate(camera_position, rads, vec3(axis.x, axis.y, axis.z));

	target_position = vec3(target_pose.p.x, target_pose.p.y, target_pose.p.z);
	camera_position += target_position;

	//if (cam_translate.z > 0.0f) global_up *= -1.0f;	// If the camera goes too close to the target, flip it 

	view_matrix = lookAt(camera_position, target_position + vec3(0,5,0), global_up);
}

mat4 Camera::get_view_matrix()
{
	return view_matrix;
}

mat4 Camera::get_projection_matrix()
{
	return projection_matrix;
}

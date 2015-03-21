#include "Camera.h"

Camera::Camera(INIReader* config, PxRigidActor* init_focalTarget)
{
	projection_matrix = perspective(
		(float)config->GetReal("camera", "fov", 60.0)/180.0f*PxPi,
		(float)config->GetInteger("window", "width", 800)/(float)config->GetInteger("window", "height", 600),
		0.1f, 10000.0f);

	cam_translate = vec3(
		(float)config->GetReal("camera", "x", 0.0),
		(float)config->GetReal("camera", "y", 5.0),
		(float)config->GetReal("camera", "z", -10.0));
	cam_rotate = 0.0f;
	focalTarget = init_focalTarget;		// This is what the camera will be tracking

	light_height = (float)config->GetReal("camera", "light_height", 700.0);

	up = normalize(PhysxAgent::toVec3(focalTarget->getGlobalPose().q.rotate(PxVec3(0,1,0))));
	forward = normalize(PhysxAgent::toVec3(focalTarget->getGlobalPose().q.rotate(PxVec3(0,0,1))));
	target = PhysxAgent::toVec3(focalTarget->getGlobalPose().p);

	forward_percent = (float)config->GetReal("camera", "forward_percent", 1.0);
	up_percent = (float)config->GetReal("camera", "up_percent", 1.0);
	if (forward_percent > 1.f) forward_percent = 1.f;
	if (forward_percent < 0.f) forward_percent = 0.f;
	if (up_percent > 1.f) up_percent = 1.f;
	if (up_percent < 0.f) up_percent = 0.f;
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

	vec3 new_target = PhysxAgent::toVec3(focalTarget->getGlobalPose().p);
	if ((new_target - target).length() > 1.f)
	{
		target = new_target;

		PxQuat new_orientation = focalTarget->getGlobalPose().q;
		up = normalize(up)*(1.f-up_percent) + normalize(PhysxAgent::toVec3(new_orientation.rotate(PxVec3(0,1,0)))) * up_percent;
		forward = normalize(forward)*(1.f-forward_percent) + normalize(PhysxAgent::toVec3(new_orientation.rotate(PxVec3(0,0,1)))) * forward_percent;

		// Set up the camera's position
		vec3 camera_position = cam_translate;	// Set the initial camera position 
		camera_position = rotateY(camera_position, cam_rotate); // If there was any rotation, we need to take that into account for position as well

		// This will rotate the camera so that it is always rotating relative to the focal target
		PxQuat orientation = PhysxAgent::PxLookAt(forward, up);
		PxReal rads;
		PxVec3 axis;
		orientation.toRadiansAndUnitAxis(rads, axis);
		camera_position = rotate(camera_position, rads, vec3(axis.x, axis.y, axis.z));

		camera_position += target;

		up = normalize(PhysxAgent::toVec3(orientation.rotate(PxVec3(0,1,0))));
		forward = normalize(PhysxAgent::toVec3(orientation.rotate(PxVec3(0,0,1))));

		view_matrix = lookAt(camera_position, target + up*3.f, up);
	}
}

mat4 Camera::get_view_matrix()
{
	return view_matrix;
}

mat4 Camera::get_projection_matrix()
{
	return projection_matrix;
}

vec3 Camera::get_light()
{
	return target + (normalize(up) * light_height);
}
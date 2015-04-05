#include "Camera.h"

Camera::Camera(INIReader* config, PxRigidActor* init_focalTarget, int width, int height, MapTypes map)
{
	projection_matrix = perspective(
		(float)config->GetReal("camera", "fov", 60.0)/180.0f*PxPi,
		width/(float)height, 0.1f, 10000.0f);

	cam_translate = vec3(
		(float)config->GetReal("camera", "x", 0.0),
		(float)config->GetReal("camera", "y", 5.0),
		(float)config->GetReal("camera", "z", -10.0));
	cam_rotate = 0.0f;
	focalTarget = init_focalTarget;		// This is what the camera will be tracking

	light_height = (float)config->GetReal("camera", "light_height", 700.0);
	look_above = (float)config->GetReal("camera", "look_above", 3.0);

	target = focalTarget->getGlobalPose();
	map_type = map;
	switch (map_type)
	{
	case PLANE:
		up = PxVec3(0,1,0);
		break;
	case SPHERE:
		up = target.p.getNormalized();
		break;
	default:
		up = target.q.rotate(PxVec3(0,1,0)).getNormalized();
		break;
	}
	forward = target.q.rotate(PxVec3(0,0,1)).getNormalized();

	forward_percent = (float)config->GetReal("camera", "forward_percent", 1.0);
	if (forward_percent > 1.f) forward_percent = 1.f;
	if (forward_percent < 0.f) forward_percent = 0.f;
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

	target = focalTarget->getGlobalPose();

	switch (map_type)
	{
	case PLANE:
		break;
	case SPHERE:
		up = target.p.getNormalized();
		break;
	default:
		up = target.q.rotate(PxVec3(0,1,0)).getNormalized();
		break;
	}
	forward = (forward * (1.f-forward_percent)) + (target.q.rotate(PxVec3(0,0,1)) * forward_percent);
	forward.normalize();

	// Set up the camera's position
	vec3 camera_position = cam_translate;	// Set the initial camera position 
	camera_position = rotateY(camera_position, cam_rotate); // If there was any rotation, we need to take that into account for position as well

	// This will rotate the camera so that it is always rotating relative to the focal target
	PxQuat orientation = PhysxAgent::PxLookAt(forward, up);
	PxReal rads;
	PxVec3 axis;
	orientation.toRadiansAndUnitAxis(rads, axis);
	camera_position = rotate(camera_position, rads, vec3(axis.x, axis.y, axis.z));

	camera_position += PhysxAgent::toVec3(target.p);

	view_matrix = lookAt(camera_position, PhysxAgent::toVec3(target.p + up*look_above), PhysxAgent::toVec3(up));
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
	return PhysxAgent::toVec3(target.p + up * light_height);
}
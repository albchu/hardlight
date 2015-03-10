#include "Camera.h"

Camera::Camera(PxRigidActor* init_actor) {
	type = CAMERA;
	actor = init_actor;
	renderable = false;
}

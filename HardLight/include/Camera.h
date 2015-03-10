#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Entity.h"
#include <glm\gtx\rotate_vector.hpp>
#include "Rendering\TextureMap.h"
#include "Vehicle/Bike.h"

class Camera : public Entity {
private:

public:
	Camera(PxRigidActor* init_actor);
};

#endif
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Entity.h"
#include "../inih/cpp/INIReader.h"
#include "Rendering\TextureMap.h"
#include "Vehicle/Chassis.h"
#include "MapTypes.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\rotate_vector.hpp>

using namespace glm;

class Camera //: public Entity 
{
private:
	mat4 projection_matrix;
	mat4 view_matrix;
	vec3 cam_translate;
	float cam_rotate;
	PxTransform target;
	PxVec3 forward;
	PxVec3 up;
	PxRigidActor* focalTarget;
	float look_above;
	float light_height;
	float forward_percent;
	MapTypes map_type;

public:
	Camera(INIReader* config, PxRigidActor* init_focalTarget, int width, int height, MapTypes map);
	void update_translationZ(float translation);
	void update_rotation(float rads);
	void update(float translationZ, float rotationRads);

	mat4 get_view_matrix();
	mat4 get_projection_matrix();
	vec3 get_light();
};

#endif
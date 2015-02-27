#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "Entity.h"

class SkyBox : public Entity
{
public:
	SkyBox(PxRigidActor* actor, MeshData* meshdata, const char* texture);
	virtual mat4 get_model_matrix();
};

#endif
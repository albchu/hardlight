#ifndef _SKYBOX_H_
#define _SKYBOX_H_

/*
 * Skybox class
 * 
 * A cube that follows the player and the inside is textured.
 *
 */

#include "Entity.h"

class SkyBox : public Entity
{
public:
	SkyBox();
	SkyBox(PxRigidActor* actor, MeshData* meshdata, GLuint);
	~SkyBox();
	virtual mat4 get_model_matrix();
};

#endif
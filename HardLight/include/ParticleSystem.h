
#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "Entity.h"

class ParticleSystem : public Entity {
private:

	GLuint coefficient_id, percent_id, radii_id;
	GLfloat coefficient, percentFactor, radii;
	physx::PxParticleSystem* particleSystem;
	void init_particle_openGL();

public:
	ParticleSystem();
	ParticleSystem(PxRigidActor*, MeshData*, GLuint);
	~ParticleSystem();
	void updateBuffer();

	physx::PxParticleSystem* getParticleSystem();
	void setParticleSystem(physx::PxParticleSystem*);

	virtual void render(mat4, mat4, vec3);

	virtual mat4 get_model_matrix();
};

#endif

#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include "ParticleData.h"
#include "Entity.h"

class ParticleSystem : public Entity {
private:

	double creationTime;
	GLuint coefficient_id, percent_id, radii_id;
	GLfloat coefficient, percentFactor, radii;
	physx::PxParticleSystem* particleSystem;
	ParticleData particleData;
	void init_particle_openGL();

public:
	ParticleSystem(PxRigidActor*, MeshData*, GLuint, GLuint);
	~ParticleSystem();

	bool isOld(double, double);
	
	physx::PxParticleSystem* getParticleSystem();
	void setParticleSystem(physx::PxParticleSystem*);

	ParticleData getParticleData();
	void setParticleData(ParticleData);

	void updateBuffer();
	virtual void render(mat4, mat4, vec3);

	virtual mat4 get_model_matrix();
};

#endif
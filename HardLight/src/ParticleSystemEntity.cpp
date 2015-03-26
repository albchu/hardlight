

#include "ParticleSystemEntity.h"
#include "ParticleFactory.h"

void ParticleSystemEntity::init_particle_openGL() {
	program_id = LoadShaders("Particle_vs.glsl", "Particle_fs.glsl");

	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	texture_id = glGetUniformLocation(program_id, "sampler");

	mvp_matrix_id = glGetUniformLocation(program_id, "MVP");
	coefficient_id = glGetUniformLocation(program_id, "coefficient");
	percent_id = glGetUniformLocation(program_id, "percentFactor");
	radii_id = glGetUniformLocation(program_id, "radii");

	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER,
		mesh_data->getVertices()->size() * sizeof(vec3),
		&mesh_data->getVertices()->at(0),
		GL_STATIC_DRAW);

	glUseProgram(program_id);
}

ParticleSystemEntity::ParticleSystemEntity() {
	type = UNDECLARED;
	draw_mode = GL_POINTS;
	renderable = true;
}
	
ParticleSystemEntity::ParticleSystemEntity(PxRigidActor* init_actor, MeshData* init_mesh_data, GLuint new_texture) {
	type = UNDECLARED;
	draw_mode = GL_POINTS;
	actor = init_actor;
	mesh_data = init_mesh_data;
	texture = new_texture;
	init_particle_openGL();
	renderable = true;
	coefficient = 10.0f;
	percentFactor = 100.0f;
	radii = 0.6f;
}

ParticleSystemEntity::~ParticleSystemEntity() {
}

physx::PxParticleSystem* ParticleSystemEntity::getParticleSystem() {
	return particleSystem;
}

void ParticleSystemEntity::setParticleSystem(physx::PxParticleSystem* system) {
	particleSystem = system;
}

void ParticleSystemEntity::render(mat4 projection_matrix, mat4 view_matrix, vec3 light) {

	mesh_data = ParticleFactory::createMeshData(particleSystem);

	glUseProgram(program_id);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_TEXTURE_2D);

	mat4 model_matrix = this->get_model_matrix();

	mat4 mvp_matrix = projection_matrix * view_matrix * model_matrix;

	glUniformMatrix4fv(mvp_matrix_id, 1, GL_FALSE, &mvp_matrix[0][0]);
	glUniform1f(coefficient_id, coefficient);
	glUniform1f(percent_id, percentFactor);
	glUniform1f(radii_id, radii);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(texture_id, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDrawArrays(draw_mode, 0, mesh_data->getVertices()->size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glDisable(GL_TEXTURE_2D);
}

mat4 ParticleSystemEntity::get_model_matrix() {
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));

	return model_matrix;
}
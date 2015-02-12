//==============================================================================
#include "HardLight.h"

float getRandFloat(float low, float high)
{
	return (low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low))));
}

//==============================================================================
bool HardLight::DrawEntity(Entity entity)
{
	PxRigidActor* actor = entity.get_actor()->isRigidActor();
	mat4 model;// = entity.get_model();

	// Update the model matrix of the entity with physx changes
	PxTransform gPose = actor->getGlobalPose();
	//model = translate(model, vec3(gPose.p.x, gPose.p.y, gPose.p.z));
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	//model = rotate(model, (GLfloat) (rads*180.0/PxPi), vec3(axis.x, axis.y, axis.z));

	

	// Load vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, entity.get_vbo());
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec3) * entity.get_mesh().size(),	// byte size of Vec3f, 4 of them
		entity.get_mesh().data(),		// pointer (Vec3f*) to contents of verts
		GL_STATIC_DRAW);	// Usage pattern of GPU buffer

	// RGB values for the vertices
	std::vector<glm::vec3> colors;
	for (int i = 0; i < entity.get_mesh().size(); i++)
	{
		//float r = getRandFloat(0.30, 1.0);
		//float g = getRandFloat(0.60, 1.0);
		//float b = getRandFloat(0.70, 1.0);
		colors.push_back(glm::vec3(0.5,0.5,0.5));//(r, g, b));
	}

	glBindBuffer(GL_ARRAY_BUFFER, entity.get_cbo());
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec3)*colors.size(),
		colors.data(),
		GL_STATIC_DRAW);

	// Load entity MVP 
	mat4 mvp = projection_matrix * view_matrix * model;
	GLint mvpID = glGetUniformLocation(entity.get_program_id(), "MVP");
	
	glUseProgram(entity.get_program_id());
	glUniformMatrix4fv(mvpID,		// ID
		1,		// only 1 matrix
		GL_FALSE,	// transpose matrix, Mat4f is row major
		glm::value_ptr(mvp)	// pointer to data in Mat4f
		);

	glUseProgram(entity.get_program_id());
	glBindVertexArray(entity.get_vao());
	GLfloat width = 25;
	glLineWidth(width);
	glDrawArrays(GL_LINE_LOOP, 0, entity.get_mesh().size());

	return false;
}

//------------------------------------------------------------------------------
void HardLight::OnRender()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msGraphics < 1000 / 60) return;
	msGraphics = msCurrent;

	//glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//// camera, will enable keyboard control at the moment with the shitty opengl 2 way
	view_matrix = translate(view_matrix, vec3((right-left)*speed, 0.0f, (forward-back)*speed));

	for(int i = 0; i < world.getEntities().size(); i++)
	{
		if ( world.getEntities()[i].get_actor()->getOwnerClient() == PX_DEFAULT_CLIENT)
		{
			DrawEntity(world.getEntities()[i]);
		}
	}

	SDL_GL_SwapWindow(window);

}

//==============================================================================

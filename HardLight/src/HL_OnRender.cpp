//==============================================================================
#include "HardLight.h"
#include <glm\gtx\rotate_vector.hpp>

float Scale;
int i = 0;
PxTransform newPos;
//==============================================================================
void HardLight::OnRender()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msGraphics < 1000 / 60) return;
	msGraphics = msCurrent;

	//Chassis* bike = bike_manager->get_player_bikes()[0];
	if (bike_manager->get_player_bikes().size() > 0)
	{
		Chassis* bike = bike_manager->get_player_bikes()[0];
		newPos = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
	}

	skybox->set_actor(pxAgent->get_physics()->createRigidStatic(newPos));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera controls
	cam_translate += vec3(0.0f, 0.0f, (forward-back)*speed);
	cam_rotate += (right-left)*speed / 30.0f;
	if (cam_rotate > PxTwoPi) cam_rotate -= PxTwoPi;
	if (cam_rotate < 0.0f) cam_rotate += PxTwoPi;

	vec3 camera_position = cam_translate;	// Set the initial camera position
	camera_position = rotateY(camera_position, cam_rotate);
	vec3 light(newPos.p.x + 00.0f, newPos.p.y + 1000.0f, newPos.p.z + 00.0f);

	// This will rotate the camera so that it is always rotating relative to bike
	PxReal rads;
	PxVec3 axis;
	newPos.q.toRadiansAndUnitAxis(rads, axis);
	camera_position = rotate(camera_position, rads, vec3(axis.x, axis.y, axis.z));

	vec3 v_pos(newPos.p.x, newPos.p.y, newPos.p.z);
	vec3 up(0.0f, 1.0f, 0.0f);
	//if (cam_translate.z > 0.0f) up *= -1.0f;
	camera_position += v_pos;
	mat4 view_matrix = lookAt(camera_position, v_pos + vec3(0,5,0), up);

	for(Viewports::Viewport viewport: viewports)
	{
		// PLACEHOLDER: For each player id in the viewport, update that camera setting and get the proj and view matrices

		glViewport(viewport.x, viewport.y, viewport.width, viewport.height );
		for(unsigned int i = 0; i < world.getEntities().size(); i++)
		{
			if(world.getEntities()[i]->is_renderable())
				world.getEntities()[i]->render(projection_matrix, view_matrix, light);
		}
	}

	SDL_GL_SwapWindow(window);

}

//==============================================================================

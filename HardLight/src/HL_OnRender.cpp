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
		Chassis* bike = bike_manager->get_player_bikes()[0]->get_chassis();
		newPos = bike->getVehicle4W()->getRigidDynamicActor()->getGlobalPose();
	}

	skybox->set_actor(pxAgent->get_physics()->createRigidStatic(newPos));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec3 light(newPos.p.x + 00.0f, newPos.p.y + 1000.0f, newPos.p.z + 00.0f);

	for(Viewports::Viewport viewport: viewports)
	{
		// PLACEHOLDER: For each player id in the viewport, update that camera setting and get the proj and view matrices
		viewport.camera->update((forward-back)*speed, (right-left)*speed);
		glViewport(viewport.x, viewport.y, viewport.width, viewport.height );
		for(unsigned int i = 0; i < world.getEntities().size(); i++)
		{
			if(world.getEntities()[i]->is_renderable())
				world.getEntities()[i]->render(viewport.camera->get_projection_matrix(), viewport.camera->get_view_matrix(), light);
		}
	}

	SDL_GL_SwapWindow(window);

}

//==============================================================================

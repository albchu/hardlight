//==============================================================================
#include "HardLight.h"
#include <glm\gtx\rotate_vector.hpp>

//==============================================================================
void HardLight::OnRender()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msGraphics < 1000 / 60) return;
	msGraphics = msCurrent;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i < viewports.size(); i++)
	{
		Viewports::Viewport viewport = viewports[i];

		FTPoint spacing(5,0,0);
		font->FaceSize(80);
		font->CharMap(ft_encoding_unicode);

		Player_Controller* controller = (Player_Controller*)bike_manager->get_player_bikes()[i % bike_manager->get_player_bikes().size()]->get_controller();
		
		viewport.camera->update((controller->get_camera_up())*speed, (controller->get_camera_right())*speed);
		glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
		for(unsigned int i = 0; i < world.getEntities().size(); i++)
		{
			if(world.getEntities()[i]->is_renderable())
				world.getEntities()[i]->render(viewport.camera->get_projection_matrix(), viewport.camera->get_view_matrix(), viewport.camera->get_light());
		}
		FTPoint messagePos(viewport.x + (viewport.width/2.0f) - 200, viewport.y + 250, 190);
		FTPoint subMessagePos(viewport.x + (viewport.width/2.0f) - 200, viewport.y + (viewport.height/3.0f), 190);

		if(scene == PAUSE) {
			winMessage = "";
			loseMessage = "";
			resetMessage = "";

			font->Render("PAUSED", -1, messagePos, spacing);
		}

		if(viewport.id == winner) {
			font->Render(winMessage, -1, messagePos, spacing);

			font->FaceSize(40);
			font->Render(resetMessage, -1, subMessagePos, spacing);
		}
		else {
			font->Render(loseMessage, -1, messagePos, spacing);

			font->FaceSize(40);
			font->Render(resetMessage, -1, subMessagePos, spacing);
		}
	}

	//if(msCurrent <= messageTime + messageTimeSpan) {
	//	FTPoint spacing(2, 0, 0);
	//	FTPoint position(viewport.x + (viewport.width/1.5f), viewport.y + (viewport.height/1.5f), 190);
	//	font->FaceSize(10);
	//}

	SDL_GL_SwapWindow(window);

}

//==============================================================================

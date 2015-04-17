//==============================================================================
#include "HardLight.h"
#include <glm\gtx\rotate_vector.hpp>

//==============================================================================
void HardLight::OnRender()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msGraphics < 1000 / 60) return;
	timer += msCurrent - msGraphics;
	msGraphics = msCurrent;
	stringstream ss;
	FTPoint spacing(5,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i < viewports.size(); i++)
	{
		Viewports::Viewport viewport = viewports[i];

		
		font->FaceSize(80);
		font->CharMap(ft_encoding_unicode);
		if( bike_manager->get_player_bikes().size() > i && controllers.size() > i)
		{
			Player_Controller* controller = (Player_Controller*)bike_manager->get_player_bikes()[i % bike_manager->get_player_bikes().size()]->get_controller();

			viewport.camera->update((controller->get_camera_up())*speed, (controller->get_camera_right())*speed);
		}
		else
		{
			viewport.camera->update(0.f, 0.f);
		}
		glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
		for(unsigned int k = 0; k < world.getEntities().size(); k++)
		{
			if(world.getEntities()[k]->is_renderable())
				//world.getEntities()[k]->render(viewport.camera->get_projection_matrix(), lookAt(vec3(0,size*1.5f,0),vec3(0,0,0), vec3(1,0,0)), viewport.camera->get_light());
				world.getEntities()[k]->render(viewport.camera->get_projection_matrix(), viewport.camera->get_view_matrix(), viewport.camera->get_light());
		}
		FTPoint messagePos(viewport.x + (viewport.width/2.0f) - 200, viewport.y + viewport.height/2 + 30, 190);
		FTPoint subMessagePos(viewport.x + (viewport.width/2.0f) - 200, viewport.y + viewport.height/2 - 30, 190);
		if(timer<3000){
			ss.str("");
			ss<<(4000-timer)/1000;
			font->Render(ss.str().c_str(), -1, messagePos, spacing);
		}
		else if(scene == PAUSE) {

			font->Render("PAUSED", -1, messagePos, spacing);
		}
		else if(scene == GAME_OVER) {
			font->Render(viewport.message, -1, messagePos, spacing);

			font->FaceSize(40);
			font->Render("Press Back or 'r'", -1, subMessagePos, spacing);
		}
		else if(scene == GAME) {
			if (powerUpMessage[0] == '\0' && bike_manager->get_all_bikes().size() > 0){
				Bike* b = bike_manager->get_all_bikes()[i % bike_manager->get_all_bikes().size()];
				switch (b->power)
				{
				case 0:
					powerUpMessage = "Jump";
					break;
				case 1:
					powerUpMessage = "Invincible";
					break;
				case 2:
					powerUpMessage = "Super Tail";
					break;
				default:
					powerUpMessage = "";
					break;
				}
				font->FaceSize(40);
				messagePos = FTPoint(viewport.x + 10, viewport.y + 10, 190);
				font->Render(powerUpMessage, -1, messagePos, spacing);
				powerUpMessage = "";
			}
		}
	}
	FTPoint mid(window_width/2 -20 , window_height - 30, 190);
	int min = timer/60000;
	int sec = (timer%60000)/1000; 
	ss.str("");
	ss<<min<<":"<<sec-3;
	font->Render(ss.str().c_str(), -1, mid, spacing);
	SDL_GL_SwapWindow(window);

}

//==============================================================================

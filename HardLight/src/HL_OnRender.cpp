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

	for(Viewports::Viewport viewport : viewports)
	{
		FTPoint spacing(5,0,0);
		font->FaceSize(80);
		font->CharMap(ft_encoding_unicode);

		// PLACEHOLDER: For each player id in the viewport, update that camera setting and get the proj and view matrices
		viewport.camera->update((forward-back)*speed, (right-left)*speed);
		glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
		for(unsigned int i = 0; i < world.getEntities().size(); i++)
		{
			if(world.getEntities()[i]->is_renderable())
				world.getEntities()[i]->render(viewport.camera->get_projection_matrix(), viewport.camera->get_view_matrix(), viewport.camera->get_light());
		}
		FTPoint messagePos(viewport.x + (viewport.width/2.0f) - 200, viewport.y + 250, 190);
		FTPoint subMessagePos(viewport.x + (viewport.width/2.0f) - 200, viewport.y + (viewport.height/3.0f), 190);

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


	//// Set the font size and render a small text.
	//FTPoint spacing(5,0,0);
	////font->Render("Hello World!"	, 2, position, spacing);
	//FTPoint position(500, 600, 190);
	//font->FaceSize(80);
	////font->Depth(10);
	////font->Outset(0, 3);
	//font->CharMap(ft_encoding_unicode);
	////font->Render("Hello FTGL!");
	//font->Render(message,-1, position, spacing);
	SDL_GL_SwapWindow(window);

}

//==============================================================================

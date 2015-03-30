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

	for(Viewports::Viewport viewport: viewports)
	{
		// PLACEHOLDER: For each player id in the viewport, update that camera setting and get the proj and view matrices
		viewport.camera->update((forward-back)*speed, (right-left)*speed);
		glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
		for(unsigned int i = 0; i < world.getEntities().size(); i++)
		{
			if(world.getEntities()[i]->is_renderable())
				world.getEntities()[i]->render(viewport.camera->get_projection_matrix(), viewport.camera->get_view_matrix(), viewport.camera->get_light());
		}
	}



	// Set the font size and render a small text.
	//font->FaceSize(80);
	//FTPoint position(500,50,50);
	//FTPoint spacing(500,0,0);
	//font->Render("Hello World!"	, 2, position, spacing);
	font->FaceSize(10);
	font->Depth(10);
	font->Outset(0, 3);
	font->CharMap(ft_encoding_unicode);
	font->Render("Hello World!");
	SDL_GL_SwapWindow(window);

}

//==============================================================================

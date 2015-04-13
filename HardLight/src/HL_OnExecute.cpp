//==============================================================================
#include "HardLight.h"

//==============================================================================
int HardLight::OnExecute()
{
	if (!OnInit())
		return EXIT_FAILURE;
	if (!BuildScene())
		return EXIT_FAILURE;

	SDL_Event Event;

	while(running)
	{

		while(SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}

		if(menu_active)
		{
			scene = PAUSE;
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			//Render current frame
			gTextTexture->render( ( window_width - gTextTexture->getWidth() ) / 2, ( window_height - gTextTexture->getHeight() ) / 2 );

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
		else
		{
			if(scene != PAUSE) {
				OnLoop();
			}
			OnRender();
		}





	}

	//OnCleanup();

	return EXIT_SUCCESS;
}

//==============================================================================

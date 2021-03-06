//==============================================================================
#include "HardLight.h"

//==============================================================================
int HardLight::OnExecute()
{
	if (!OnInit())
		return EXIT_FAILURE;
	if (!menu_init())
		return EXIT_FAILURE;

	SDL_Event Event;

	while(running)
	{

		while(SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}

		Uint32 msCurrent = SDL_GetTicks();
		if(scene == GAME && !menu_active) timer += msCurrent - msGraphics;
		msGraphics = msCurrent;

		if(menu_active)
		{
			scene = PAUSE;
			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			menuManager->render();

			//Update screen
			SDL_RenderPresent( gRenderer );
			menu_update();
		}
		else if (!menu_active && scene_built)
		{
			if(scene != PAUSE &&(timer < 1 || timer > 3000)) {
				OnLoop();
			}
			OnRender();
		}

	}

	//OnCleanup();

	return EXIT_SUCCESS;
}

//==============================================================================

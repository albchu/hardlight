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

		if(scene == GAME) {

			while(SDL_PollEvent(&Event))
			{
				OnEvent(&Event);
			}

			OnLoop();
			OnRender();
		}
		else {

			while(SDL_PollEvent(&Event))
			{
				running = gui.onGUIEvent(&Event);
			}

			gui.render();

		}
	}

	OnCleanup();

	return EXIT_SUCCESS;
}

//==============================================================================

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

		if(scene == GAME) {
			OnLoop();
			OnRender();
		}
	}

	OnCleanup();

	return EXIT_SUCCESS;
}

//==============================================================================

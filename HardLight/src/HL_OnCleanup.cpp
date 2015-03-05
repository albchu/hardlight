//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnCleanup()
{
	for(Bike* aBike : bikes->get_all_bikes())
	{
		aBike->getVehicle4W()->getRigidDynamicActor()->release();
		aBike->getVehicle4W()->free();

		aBike->getBatchQuery()->release();
		aBike->getVehicleSceneQueryData()->free(pxAgent->get_allocator());
	}

	gFrictionPairs->release();
	PxCloseVehicleSDK();
	pxAgent->cleanup();
	PxCloseExtensions();

	if (glcontext != NULL) SDL_GL_DeleteContext(glcontext);
	if (window != NULL) SDL_DestroyWindow(window);
	SDL_Quit();
}

//==============================================================================

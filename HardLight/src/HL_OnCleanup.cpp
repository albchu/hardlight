//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnCleanup()
{
	for(Bike* aBike : bike_manager->get_all_bikes())
	{
		aBike->getVehicle4W()->getRigidDynamicActor()->release();
		aBike->getVehicle4W()->free();
		// Note for future onlookers: we need to detatch all shapes from actors https://developer.nvidia.com/sites/default/files/akamai/physx/Manual/Shapes.html
		aBike->getBatchQuery()->release();
		aBike->getVehicleSceneQueryData()->free(pxAgent->get_allocator());
	}

	gFrictionPairs->release();
	pxAgent->cleanup();

	if (glcontext != NULL) SDL_GL_DeleteContext(glcontext);
	if (window != NULL) SDL_DestroyWindow(window);
	SDL_Quit();
}

//==============================================================================

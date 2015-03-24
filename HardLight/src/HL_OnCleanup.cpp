//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnCleanup()
{
	for(Bike* aBike : bike_manager->get_all_bikes())
	{
		aBike->get_chassis()->getVehicle4W()->getRigidDynamicActor()->release();
		aBike->get_chassis()->getVehicle4W()->free();
		// Note for future onlookers: we need to detatch all shapes from actors https://developer.nvidia.com/sites/default/files/akamai/physx/Manual/Shapes.html
		aBike->get_chassis()->getBatchQuery()->release();
		aBike->get_chassis()->getVehicleSceneQueryData()->free(pxAgent->get_allocator());
	}

	for(Bike* aBike : bike_manager->get_player_bikes())
	{
		delete (Player_Controller*)aBike->get_controller();
	}

	gFrictionPairs->release();
	pxAgent->cleanup();

	if (glcontext != NULL) SDL_GL_DeleteContext(glcontext);
	if (window != NULL) SDL_DestroyWindow(window);
	SDL_Quit();
}

//==============================================================================

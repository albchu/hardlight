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
		aBike->getVehicleSceneQueryData()->free(gAllocator);
	}

	gFrictionPairs->release();
	PxCloseVehicleSDK();
	pxAgent->cleanup();
	//if (gScene != NULL) gScene->release();
	if (gDispatcher != NULL) gDispatcher->release();
	PxCloseExtensions();
	//PxProfileZoneManager* profileZoneManager = pxAgent->get_physics()->getProfileZoneManager()->release();
	//profileZoneManager->release();
	if (gConnection != NULL) gConnection->release();
	//if (gPhysics != NULL) gPhysics->release();
	if (gFoundation != NULL) gFoundation->release();

	if (glcontext != NULL) SDL_GL_DeleteContext(glcontext);
	if (window != NULL) SDL_DestroyWindow(window);
	SDL_Quit();
}

//==============================================================================

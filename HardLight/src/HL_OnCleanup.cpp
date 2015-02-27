//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnCleanup()
{
	bike->getVehicle4W()->getRigidDynamicActor()->release();
	bike->getVehicle4W()->free();
	gGroundPlane->release();
	bike->getBatchQuery()->release();
	bike->getVehicleSceneQueryData()->free(gDefaultAllocator);
	gFrictionPairs->release();
	PxCloseVehicleSDK();
	world.clear();	
	if (gScene != NULL) gScene->release();
	if (gPhysics != NULL) gPhysics->release();
	if (gFoundation != NULL) gFoundation->release();

	if (glcontext != NULL) SDL_GL_DeleteContext(glcontext);
	if (window != NULL) SDL_DestroyWindow(window);
	SDL_Quit();
}

//==============================================================================

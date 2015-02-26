//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::OnCleanup()
{
	gVehicle4W->getRigidDynamicActor()->release();
	gVehicle4W->free();
	gGroundPlane->release();
	gBatchQuery->release();
	gVehicleSceneQueryData->free(gDefaultAllocator);
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

//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::DrawRigidActor(PxRigidActor* actor)
{
	glLoadIdentity();
	PxTransform gPose = actor->getGlobalPose();
	glTranslatef(gPose.p.x, gPose.p.y, gPose.p.z);

	PxU32 nShapes = actor->getNbShapes();
	PxShape** shapes = new PxShape*[nShapes];
	actor->getShapes(shapes, nShapes);
	for (unsigned int i = 0; i < nShapes; i++)
	{
		glPushMatrix();

		PxTransform lPose = shapes[i]->getLocalPose();
		glTranslatef(lPose.p.x, lPose.p.y, lPose.p.z);

		GLUquadricObj * quad = gluNewQuadric();
		gluQuadricDrawStyle(quad, GLU_FILL);
		gluQuadricNormals(quad, GLU_SMOOTH); 
		gluQuadricOrientation(quad, GLU_OUTSIDE);

		PxGeometryType::Enum type = shapes[i]->getGeometryType();
		PxSphereGeometry sphere;
		PxBoxGeometry box;
		switch(type)
		{
		case PxGeometryType::eSPHERE:
			
			if (!shapes[i]->getSphereGeometry(sphere)) return;
			gluSphere(quad, sphere.radius, 9, 7);
			break;
		case PxGeometryType::eBOX:
			
			if (!shapes[i]->getBoxGeometry(box)) return;
			gluSphere(quad, box.halfExtents.x, 9, 7);
			break;
		}

		gluDeleteQuadric(quad);
		glPopMatrix();
	}
	delete shapes;
}

//------------------------------------------------------------------------------
void HardLight::OnRender()
{
	Uint32 msCurrent = SDL_GetTicks();
	if (msCurrent - msGraphics < 1000 / 60) return;
	msGraphics = msCurrent;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, window_width/(float)window_height, 1.0f, 10000.0f);
	gluLookAt(gCameraPos.x, gCameraPos.y, gCameraPos.z,
		gCameraPos.x + gCameraForward.x, gCameraPos.y + gCameraForward.y, gCameraPos.z + gCameraForward.z,
		0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	glColor3f(0.7f, 0.7f, 0.7f);

	for(int i=-grid_size; i<=grid_size; i++)
	{
		glVertex3f((float)i,0,(float)-grid_size);
		glVertex3f((float)i,0,(float)grid_size);

		glVertex3f((float)-grid_size,0,(float)i);
		glVertex3f((float)grid_size,0,(float)i);
	}
	glEnd();

	PxActorTypeFlags desiredTypes = PxActorTypeFlag::eRIGID_STATIC
		| PxActorTypeFlag::eRIGID_DYNAMIC;
	PxU32 count = gScene->getNbActors(desiredTypes);
	PxActor** buffer = new PxActor*[count];
	gScene->getActors(desiredTypes, buffer, count);
	for(PxU32 i = 0; i < count; i++)
	{
		if (buffer[i]->getOwnerClient() == PX_DEFAULT_CLIENT)   //skip actors owned by foreign clients
		{
			DrawRigidActor(buffer[i]->isRigidActor());
		}
	}
	delete buffer;

	SDL_GL_SwapWindow(window);

}

//==============================================================================

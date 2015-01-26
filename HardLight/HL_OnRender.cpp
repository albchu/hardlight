//==============================================================================
#include "HardLight.h"

//==============================================================================
void HardLight::DrawRigidActor(PxRigidActor* actor)
{
	// Actor Shading
	GLfloat ambient_cube[]={0.0f, 0.0f, 0.60f, 1.0f};
	GLfloat ambient_sphere[]={0.60f, 0.60f, 0.0f, 1.0f};

	GLfloat mat_diffuse_cube[]={0.0f, 0.0f, 0.85f, 1.0f};
	GLfloat mat_diffuse_sphere[]={0.85f, 0.85f, 0.0f, 1.0f};

	glLoadIdentity();
	PxTransform gPose = actor->getGlobalPose();
	glTranslatef(gPose.p.x, gPose.p.y, gPose.p.z);
	PxReal rads;
	PxVec3 axis;
	gPose.q.toRadiansAndUnitAxis(rads, axis);
	glRotatef((GLfloat) (rads*180/M_PI), axis.x, axis.y, axis.z);
	PxU32 nShapes = actor->getNbShapes();
	PxShape** shapes = new PxShape*[nShapes];
	actor->getShapes(shapes, nShapes);
	for (unsigned int i = 0; i < nShapes; i++)
	{
		glPushMatrix();

		PxTransform lPose = shapes[i]->getLocalPose();
		glTranslatef(lPose.p.x, lPose.p.y, lPose.p.z);
		lPose.q.toRadiansAndUnitAxis(rads, axis);
		glRotatef((GLfloat) (rads*180/M_PI), axis.x, axis.y, axis.z);
		
		PxGeometryType::Enum type = shapes[i]->getGeometryType();
		PxSphereGeometry sphere;
		GLUquadricObj * quad = gluNewQuadric();
		gluQuadricDrawStyle(quad, GLU_FILL);
		gluQuadricNormals(quad, GLU_SMOOTH); 
		gluQuadricOrientation(quad, GLU_OUTSIDE);
		PxBoxGeometry box;
		switch(type)
		{
		case PxGeometryType::eSPHERE:
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_sphere);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_sphere);
			if (!shapes[i]->getSphereGeometry(sphere)) return;
			gluSphere(quad, sphere.radius, 9, 7);
			break;

		case PxGeometryType::eBOX:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_cube);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_cube);
			if (!shapes[i]->getBoxGeometry(box)) return;
			float half = box.halfExtents.x;
			glBegin(GL_POLYGON); // front
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-half, -half, half);
			glVertex3f(half, -half, half);
			glVertex3f(half, half, half);
			glVertex3f(-half, half, half);
			glEnd();
			glBegin(GL_POLYGON); // back
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-half, half, -half);
			glVertex3f(half, half, -half);
			glVertex3f(half, -half, -half);
			glVertex3f(-half, -half, -half);
			glEnd();
			glBegin(GL_POLYGON); // right
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(half, -half, -half);
			glVertex3f(half, half, -half);
			glVertex3f(half, half, half);
			glVertex3f(half, -half, half);
			glEnd();
			glBegin(GL_POLYGON); // left
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-half, -half, half);
			glVertex3f(-half, half, half);
			glVertex3f(-half, half, -half);
			glVertex3f(-half, -half, -half);
			glEnd();
			glBegin(GL_POLYGON); // top
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(half, half, half);
			glVertex3f(half, half, -half);
			glVertex3f(-half, half, -half);
			glVertex3f(-half, half, half);
			glEnd();
			glBegin(GL_POLYGON); // bottom
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(-half, -half, half);
			glVertex3f(-half, -half, -half);
			glVertex3f(half, -half, -half);
			glVertex3f(half, -half, half);
			glEnd();
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

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
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
		glVertex3f((float)i , -0.1f, (float)-grid_size);
		glVertex3f((float)i , -0.1f, (float)grid_size);

		glVertex3f((float)-grid_size, -0.1f, (float)i);
		glVertex3f((float)grid_size, -0.1f, (float)i);
	}
	glEnd();
	
	// Set actor shading & stage lighting
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	// Stage Lighting
	GLfloat lightPosition[4] = {0.0f, 10.0f, 10.0f, 1.0f};
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lightAmbientColour);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuseColour);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightSpecularColour);
	glLightfv(GL_LIGHT0,GL_POSITION, lightPosition);

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

	glDisable(GL_LIGHTING);
	SDL_GL_SwapWindow(window);

}

//==============================================================================

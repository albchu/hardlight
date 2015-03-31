#include "Rendering/Viewports.h"

// Math is pretty difficult to dynamically calculate this on the fly so we will load based on cases
// Will not initialize camera object. That will be needed to be created later on
vector<Viewports::Viewport> Viewports::generate_viewports(int numViews, int width, int height)
{
	vector<Viewports::Viewport> viewports;

	switch(numViews)
	{
	case(1):
		{
			// Take up the whole window
			Viewport viewport1;
			viewport1.x = 0;
			viewport1.y = 0;
			viewport1.width = width;
			viewport1.height = height;
			viewport1.id = BIKE1;
			viewports.push_back(viewport1);
			break;
		}
	case(2):
		{
			Viewport viewport1;
			Viewport viewport2;

			// Top frame
			viewport1.x = 0;
			viewport1.y = height/2;
			viewport1.width = width;
			viewport1.height = height/2;
			viewport1.id = BIKE1;

			// Bottom frame
			viewport2.x = 0;
			viewport2.y = 0;
			viewport2.width = width;
			viewport2.height = height/2;
			viewport2.id = BIKE2;

			viewports.push_back(viewport1);
			viewports.push_back(viewport2);
			break;
		}
	case(3):
		{
			Viewport viewport1;
			Viewport viewport2;
			Viewport viewport3;

			// Top left frame
			viewport1.x = 0;
			viewport1.y = height/2;
			viewport1.width = width/2;
			viewport1.height = height/2;
			viewport1.id = BIKE1;

			// Top right frame
			viewport2.x = width/2;
			viewport2.y = height/2;
			viewport2.width = width/2;
			viewport2.height = height/2;
			viewport2.id = BIKE2;

			// Bottom frame
			viewport3.x = 0;
			viewport3.y = 0;
			viewport3.width = width;
			viewport3.height = height/2;
			viewport3.id = BIKE3;

			viewports.push_back(viewport1);
			viewports.push_back(viewport2);
			viewports.push_back(viewport3);
			break;
		}
	case(4):
		{
			Viewport viewport1;
			Viewport viewport2;
			Viewport viewport3;
			Viewport viewport4;

			// Top left frame
			viewport1.x = 0;
			viewport1.y = height/2;
			viewport1.width = width/2;
			viewport1.height = height/2;
			viewport1.id = BIKE1;

			// Top right frame
			viewport2.x = width/2;
			viewport2.y = height/2;
			viewport2.width = width/2;
			viewport2.height = height/2;
			viewport2.id = BIKE2;

			// Bottom left frame
			viewport3.x = 0;
			viewport3.y = 0;
			viewport3.width = width/2;
			viewport3.height = height/2;
			viewport3.id = BIKE3;
			
			// Bottom right frame
			viewport4.x = width/2;
			viewport4.y = 0;
			viewport4.width = width/2;
			viewport4.height = height/2;
			viewport4.id = BIKE4;

			viewports.push_back(viewport1);
			viewports.push_back(viewport2);
			viewports.push_back(viewport3);
			viewports.push_back(viewport4);
			break;
		}
	default:
		cerr << "Unsupported number of view ports specified" << endl;
	}

	return viewports;
}

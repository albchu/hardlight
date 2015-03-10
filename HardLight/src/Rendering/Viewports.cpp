#include "Rendering/Viewports.h"

// Math is pretty difficult to dynamically calculate this on the fly so we will load based on cases
vector<Viewports::Viewport> Viewports::generate_viewports(int numViews, float width, float height)
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
			viewports.push_back(viewport1);
			break;
		}
	case(2):
		{
			Viewport viewport1;
			Viewport viewport2;

			// Top frame
			viewport1.x = 0;
			viewport1.y = int(height/2);
			viewport1.width = width;
			viewport1.height = height/2.0f;

			// Bottom frame
			viewport2.x = 0;
			viewport2.y = 0;
			viewport2.width = width;
			viewport2.height = height/2.0f;

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
			viewport1.y = int(height/2);
			viewport1.width = width/2.0f;
			viewport1.height = height/2.0f;

			// Top right frame
			viewport2.x = int(width/2);
			viewport2.y = int(height/2);
			viewport2.width = width/2.0f;
			viewport2.height = height/2.0f;

			// Bottom frame
			viewport3.x = 0;
			viewport3.y = 0;
			viewport3.width = width;
			viewport3.height = height/2.0f;

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
			viewport1.y = int(height/2);
			viewport1.width = width/2.0f;
			viewport1.height = height/2.0f;

			// Top right frame
			viewport2.x = int(width/2);
			viewport2.y = int(height/2);
			viewport2.width = width/2.0f;
			viewport2.height = height/2.0f;

			// Bottom left frame
			viewport3.x = 0;
			viewport3.y = 0;
			viewport3.width = width/2.0f;
			viewport3.height = height/2.0f;
			
			// Bottom right frame
			viewport4.x = int(width/2);
			viewport4.y = 0;
			viewport4.width = width/2.0f;
			viewport4.height = height/2.0f;

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

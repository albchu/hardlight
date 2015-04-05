#ifndef _VIEWPORTS_H_
#define _VIEWPORTS_H_

//#include <GL\glew.h>
#include <vector>
#include <iostream>
#include "Camera.h"

using namespace std;

enum BikeID
{
	NONE,
	BIKE1,
	BIKE2,
	BIKE3,
	BIKE4,
};

class Viewports
{
public:
	struct Viewport
	{
		// Specify the lower left corner of the viewport rectangle, in pixels.
		int  x;
		int  y;

		// Specify the width and height of the viewport.
		int  width;
		int  height;

		// An ID to distinguish which camera it is for
		BikeID id;

		// 
		const char* message;

		// The camera for the particular viewport
		Camera* camera;
	};
	static vector<Viewport> generate_viewports(int numViews, int width, int height);
};

#endif
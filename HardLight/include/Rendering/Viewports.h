#ifndef _VIEWPORTS_H_
#define _VIEWPORTS_H_

//#include <GL\glew.h>
#include <vector>
#include <iostream>

using namespace std;

class Viewports
{
public:
	struct Viewport
	{
		//Specify the lower left corner of the viewport rectangle, in pixels.
		int  x;
		int  y;

		//Specify the width and height of the viewport.
		float  width;
		float  height;
	};
	static vector<Viewport> generate_viewports(int numViews, float width, float height);
};

#endif
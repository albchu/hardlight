#ifndef _VIEWPORTS_H_
#define _VIEWPORTS_H_

//#include <GL\glew.h>
#include <vector>
#include <iostream>
#include "Camera.h"

using namespace std;

enum PlayerID
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
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
		float  width;
		float  height;

		// An ID to distinguish which camera it is for
		PlayerID id;

		// The camera for the particular viewport
		Camera* camera;
	};
	static vector<Viewport> generate_viewports(int numViews, float width, float height);
};

#endif
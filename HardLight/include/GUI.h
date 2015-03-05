#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Element.h"
#include "Image.h"
#include "Button.h"
#include "../inih\cpp\INIReader.h"
#include "glm/gtx/string_cast.hpp"

class GUI {
private:
	int numOfImages, numOfButtons;
	std::vector<Element> elements;
	SDL_Surface* imagePlane;
	SDL_Renderer* renderer;
	INIReader*    loader;

	void addElement(Element);

public:
	GUI();
	GUI(SDL_Window*);
	~GUI();

	void loadMenu(const char*);
	void render();
};

#endif
#ifndef _SCENE_H_
#define _SCENE_H_

/*
 * GUI Class
 *
 * Purpose:
 *	- read menu descriptions
 *  - store elements of GUI
 *  - render elements
 *
 * Available menus: GameOver.txt, MainMenu.txt, Paused.txt
 */

#include <vector>
#include "Element.h"
#include "Image.h"
#include "Button.h"
#include "../inih\cpp\INIReader.h"
#include "glm/gtx/string_cast.hpp"

class GUI {
private:
	int numOfImages, numOfButtons;
	std::vector<Image> images;
	std::vector<Button> buttons;
	SDL_Renderer* renderer;
	INIReader*    loader;

	void addImage(Image);
	void addButton(Button);

public:
	GUI();
	GUI(SDL_Window*);
	~GUI();

	void loadMenu(const char*);
	void render(int winWidth, int winHeight, SDL_Window*);
	bool onGUIEvent(SDL_Event*);
};

#endif
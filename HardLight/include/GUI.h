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
#include <PxPhysicsAPI.h>
#include "../SceneTypes.h"
#include "Element.h"
#include "Image.h"
#include "Button.h"
#include "../inih\cpp\INIReader.h"
#include "glm/gtx/string_cast.hpp"
#include <glm/gtc/matrix_transform.hpp>

class GUI {
private:
	int numOfImages, numOfButtons;
	std::vector<Image> images;
	std::vector<Button> buttons;
	SDL_Window* win_copy;
	INIReader* loader;

	void addImage(Image);
	void addButton(Button);

public:
	GUI();
	GUI(SDL_Window*);
	~GUI();

	void loadMenu(const char*, PxPhysics*);
	void render();
	bool onGUIEvent(SDL_Event*, Scene*);
};

#endif

#include "GUI.h"
#include <string>

GUI::GUI() {
}

GUI::GUI(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

GUI::~GUI() {

}

void GUI::addElement(Element e) {
	elements.push_back(e);
}

void GUI::loadMenu(const char * menuPath) {
	loader = new INIReader(menuPath);
	if (loader->ParseError() < 0) {
		fprintf(stderr, "Can't load '%s'\n", menuPath);
		exit(EXIT_FAILURE);
    }

	numOfImages = loader->GetInteger("images", "numOfImages", 0);
	numOfButtons = loader->GetInteger("buttons", "numOfButtons", 0);

	for(int i = 0; i < numOfImages; i++) {
		std::string imagePath;
		Element image;

		imagePath = loader->Get("images", std::string("image") + std::to_string(i+1), "");
		image = Element(imagePath.c_str());

		addElement(image);
	}
}

void GUI::render() {

}
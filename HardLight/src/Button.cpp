
#include "Button.h"

Button::Button() : Element() {
}

Button::Button(const char* texturePath) : Element(texturePath) {
}

Button::~Button() {
	//SDL_FreeSurface(texture);
}

void Button::setAction(Action a) {
	command = a;
}

Action Button::getAction() {
	return command;
}
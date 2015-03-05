#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <glm/glm.hpp>

enum Action {
	GAME,
	QUIT
};

class Element {
private:
	glm::vec2 pos;
	SDL_Texture* texture;

public:
	Element();
	Element(const char*);
	~Element();

	glm::vec2 getPos();
	void setPos(glm::vec2);
};

#endif
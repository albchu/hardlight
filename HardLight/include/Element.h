#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_Image.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>


enum Action {
	START,
	QUIT
};

class Element {
protected:
	glm::vec2 pos;
	glm::vec2 size;
	std::string  texturePath;
	GLuint texture_id;
	SDL_Surface* texture;

public:
	Element();
	Element(const char*);
	~Element();

	glm::vec2 getPos();
	glm::vec2 getSize();
	SDL_Surface* getSurface();
	std::string getPath();
	GLuint getTextureID();
	void init_texture();
	void setPos(glm::vec2);
	void setSize(glm::vec2);
	void setSize(double, double);
};

#endif
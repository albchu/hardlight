
#include "Element.h"

Element::Element() {
}

Element::Element(const char* texturePath) {

	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		fprintf(stderr, "Couldn't initialize image loader.\n");
		exit(EXIT_FAILURE);
	}

	this->texturePath = std::string(texturePath);

	texture = IMG_Load(texturePath);
	if(texture == NULL) {
		fprintf(stderr, "%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

Element::~Element() {
	//SDL_FreeSurface(texture);
	//glDeleteTextures(1, &texture_id);
}

glm::vec2 Element::getPos() {
	return pos;
}

glm::vec2 Element::getSize() {
	return size;
}

SDL_Surface* Element::getSurface() {
	return texture;
}

std::string Element::getPath() {
	return texturePath;
}

GLuint Element::getTextureID() {
	return texture_id;
}

void Element::init_texture() {
	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

}

void Element::setPos(glm::vec2 newPos) {
	pos = newPos;
}

void Element::setSize(glm::vec2 newSize) {
	size = newSize;
}

void Element::setSize(double w, double h) {
	size = glm::vec2(w, h);
}
#ifndef _ELEMENT_H_
#define _ELEMENT_H_


#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <glm\gtx\rotate_vector.hpp>

#include "ShaderTools.h"
#include "Entity.h"

enum Action {
	START,
	QUIT
};

class Element : public Entity {
protected:
	vec2 pos;
	vec2 size;
	string  texturePath;
	SDL_Surface* texture;

public:
	Element();
	Element(const char*);
	~Element();

	vec2 getPos();
	vec2 getSize();
	SDL_Surface* getSurface();
	string getPath();
	GLuint getTextureID();
	void init_texture();
	void init_model(SDL_Window*);
	void setPos(vec2);
	void setSize(vec2);
	void setSize(double, double);
	virtual mat4 get_model_matrix();
};

#endif
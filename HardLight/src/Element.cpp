
#include "Element.h"

Element::Element() {
}

Element::Element(const char* texturePath) {

	draw_mode = GL_TRIANGLES;

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

vec2 Element::getPos() {
	return pos;
}

vec2 Element::getSize() {
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
	errorReport("glGenTextures");

	glBindTexture(GL_TEXTURE_2D, texture_id);
	errorReport("glBindTexture");

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);
	errorReport("glTexImage2D");

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	errorReport("glTexParameteri");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	errorReport("glTexParameteri");
}

void Element::init_model(SDL_Window* window) {
	MeshData temp;

	double x = pos.x;
	double y = pos.y;
	double z = 0.5f;
	double w = clamp(size.x, 0.0f, 1.0f);
	double h = clamp(size.y, 0.0f, 1.0f);;

	vec3 normal(0.0f, 0.0f, -1.0f);
	
	vec3 v1(x, y, z);
	vec3 v2(x + w, y, z);
	vec3 v3(x + w, y + h, z);
	vec3 v4(x, y + h, z);

	vec2 t1(0.0f, 1.0f);
	vec2 t2(1.0f, 1.0f);
	vec2 t3(1.0f, 0.0f);
	vec2 t4(0.0f, 0.0f);

	for(int i = 0; i < 6; i++)
		temp.addNormal(normal);

	temp.addVertex(v1);
	temp.addVertex(v2);
	temp.addVertex(v3);
	temp.addVertex(v1);
	temp.addVertex(v3);
	temp.addVertex(v4);

	temp.addTexture(t4);
	temp.addTexture(t3);
	temp.addTexture(t2);
	temp.addTexture(t1);
	temp.addTexture(t3);
	temp.addTexture(t1);

	mesh_data = &temp;

}

void Element::setPos(vec2 newPos) {
	pos = newPos;
}

void Element::setSize(vec2 newSize) {
	size = newSize;
}

void Element::setSize(double w, double h) {
	size = vec2(w, h);
}

mat4 Element::get_model_matrix() {
	mat4 model_matrix = mat4(1.0);
	PxTransform gPose = actor->getGlobalPose();
	model_matrix = translate(model_matrix, vec3(gPose.p.x, gPose.p.y, gPose.p.z));

	return model_matrix;
}
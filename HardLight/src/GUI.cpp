
#include "GUI.h"
#include <string>

using namespace std;
using namespace glm;

GUI::GUI() {
}

GUI::GUI(SDL_Window* window) {
	win_copy = window;
}

GUI::~GUI() {
	//delete loader;
	//delete renderer;
}

void GUI::addImage(Image i) {
	images.push_back(i);
}

void GUI::addButton(Button b) {
	buttons.push_back(b);
}

void GUI::loadMenu(const char * menuPath, PxPhysics* physics) {
	string imagePath;
	Image image;
	Button button;
	int w, h;
	float x, y;

	SDL_GetWindowSize(win_copy, &w, &h);

	loader = new INIReader(menuPath);
	if (loader->ParseError() < 0) {
		fprintf(stderr, "Can't load '%s'\n", menuPath);
		exit(EXIT_FAILURE);
    }

	numOfImages = loader->GetInteger("images", "numOfImages", 0);
	numOfButtons = loader->GetInteger("buttons", "numOfButtons", 0);

	// load images
	for(int i = 0; i < numOfImages; i++) {

		imagePath = loader->Get("images", string("image") + to_string(i+1), "");
		x = clamp((float)loader->GetReal("images", string("x") + to_string(i+1), 0.0f), 0.0f, 1.0f);
		y = clamp((float)loader->GetReal("images", string("y") + to_string(i+1), 0.0f), 0.0f, 1.0f);

		image = Image(imagePath.c_str());
		image.setPos(vec2(x, y));
		image.setSize(vec2(clamp(image.getSurface()->w, 0, 1), clamp(image.getSurface()->h, 0, 1)));
		image.init_texture();
		image.init_model(win_copy);
		image.set_actor(physics->createRigidStatic(PxTransform(x, y, 0.5f)));
		image.init_opengl();

		addImage(image);
	}

	// load buttons
	for(int i = 0; i < numOfButtons; i++) {
		int imgNum;
		string action;

		imgNum = loader->GetInteger("buttons", string("imageNum") + to_string(i+1), 1);
		action = loader->Get("buttons", string("action") + to_string(i+1), "");
		
		button = Button(images[imgNum - 1].getPath().c_str());
		
		if(action.compare("start") == 0) {
			button.setAction(START);
		}
		else if(action.compare("quit") == 0) {
			button.setAction(QUIT);
		}

		x = clamp(images[imgNum - 1].getPos().x, 0.0f, 1.0f);
		y = clamp(images[imgNum - 1].getPos().y, 0.0f, 1.0f);

		button.setPos(vec2(x, y));
		button.setSize(vec2(clamp(images[imgNum - 1].getSurface()->w, 0, 1), clamp(images[imgNum - 1].getSurface()->h, 0, 1)));
		button.init_texture();
		button.init_model(win_copy);
		button.set_actor(physics->createRigidStatic(PxTransform(x, y, 0.5f)));
		button.init_opengl();

		addButton(button);
	}
}

void GUI::render() {

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//mat4 projection = perspective(60.0f, (float)winWidth/(float)winHeight, 0.0f, 100.0f);
	mat4 projection = ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	mat4 view = lookAt(vec3(0.5f, 0.0f, -1.0f), vec3(0.5f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f));

	vec3 light = vec3(0.5f, 1.0f, 0.0f);

	for(Image i : images) {

		i.render(projection, view, light);
	}

	for(Button b : buttons) {

		b.render(projection, view, light);
	}

	SDL_GL_SwapWindow(win_copy);
}

bool GUI::onGUIEvent(SDL_Event* event, Scene* scene) {

	switch(event->type) {
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		switch(event->key.keysym.sym) {
		case SDLK_KP_ENTER:
			*scene = GAME;
			break;
		}
		break;
	}

	return true;
}
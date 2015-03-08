
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
	double x, y;

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
		x = loader->GetReal("images", string("x") + to_string(i+1), 0.0f);
		y = loader->GetReal("images", string("y") + to_string(i+1), 0.0f);

		image = Image(imagePath.c_str());
		image.setPos(vec2(x, y));
		image.setSize(vec2(image.getSurface()->w, image.getSurface()->h));
		image.init_texture();
		image.init_model(win_copy);
		image.set_actor(physics->createRigidStatic(PxTransform(PxVec3(x/w, y/h, 100.0f))));

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

		button.init_texture();
		button.init_model(win_copy);
		button.set_actor(physics->createRigidStatic(PxTransform(PxVec3(images[imgNum - 1].getPos().x/w, images[imgNum - 1].getPos().y/h, 100.0f))));

		addButton(button);
	}
}

void GUI::render() {

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//mat4 projection = perspective(60.0f, (float)winWidth/(float)winHeight, 0.0f, 100.0f);
	mat4 projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 5.0f, 100.0f);

	mat4 modelView = lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 100.0f), vec3(0.0f, 1.0f, 0.0f));

	vec3 light = vec3(0.0f, 0.0f, 0.0f);

	for(Image i : images) {

		modelView = i.get_model_matrix();
		i.render(projection, modelView, light);
	}

	for(Button b : buttons) {

		modelView = b.get_model_matrix();
		b.render(projection, modelView, light);
	}

	SDL_GL_SwapWindow(win_copy);
}

bool GUI::onGUIEvent(SDL_Event* event) {

	switch(event->type) {
	case SDL_QUIT:
		return false;
	case SDL_MOUSEBUTTONDOWN:

		break;
	}

	return true;
}
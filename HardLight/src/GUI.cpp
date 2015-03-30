
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
	float x, y;

	loader = new INIReader(menuPath);
	if (loader->ParseError() < 0) {
		fprintf(stderr, "Can't load '%s'\n", menuPath);
    }

	numOfImages = loader->GetInteger("images", "numberOfImages", 0);
	numOfButtons = loader->GetInteger("buttons", "numberOfButtons", 0);

	// load images
	for(int i = 0; i < numOfImages; i++) {

		imagePath = loader->Get("images", string("image") + to_string(i+1), "");
		x = (float)loader->GetReal("images", string("x") + to_string(i+1), 0.0);
		y = (float)loader->GetReal("images", string("y") + to_string(i+1), 0.0);

		image = Image(imagePath.c_str());
		image.setPos(vec2(x, y));
		//image.setSize(vec2(image.getSurface()->w, image.getSurface()->h));
		//image.init_texture();
		image.init_model();
		image.set_actor(physics->createRigidStatic(PxTransform(0.0f, 0.0f, 0.0f)));
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

		x = images[imgNum - 1].getPos().x;
		y = images[imgNum - 1].getPos().y;

		button.setPos(vec2(x, y));
		//button.setSize(vec2(button.getSurface()->w, button.getSurface()->h));
		//button.init_texture();
		button.init_model();
		button.set_actor(physics->createRigidStatic(PxTransform(0.0f, 0.0f, 0.0f)));
		button.init_opengl();

		addButton(button);
	}

}

void GUI::render() {

	int width, height;
	float halfWidth, halfHeight;
	SDL_GetWindowSize(win_copy, &width, &height);

	halfWidth = width/2.0f;
	halfHeight = height/2.0f;

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	mat4 projection = ortho(0.0f, (float)width, (float)height, 0.0f, 0.1f, 101.0f);
	mat4 view = lookAt(vec3(halfWidth, halfHeight, 0.0f), vec3(halfWidth, halfHeight, 100.0f), vec3(0.0f, 1.0f, 0.0f));

	vec3 light = vec3(halfWidth, 0.0f, 0.0f);

	for(Image i : images) {

		i.render(projection, view, light);
	}

	for(Button b : buttons) {

		b.render(projection, view, light);
	}

	SDL_GL_SwapWindow(win_copy);
}

bool GUI::onGUIEvent(SDL_Event* event, Scene* scene) {

	switch(event->type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		switch(event->key.keysym.sym)
		{
		case SDLK_i:
			for(unsigned int i = 0; i < images.size(); i++)
			{
				fprintf(stdout, "Position = (%.2f, %.2f)\n", images[i].getPos().x, images[i].getPos().y);
			}
			break;
		case SDLK_SPACE:
			*scene = GAME;
			break;
		}
		break;
	case SDL_CONTROLLERBUTTONDOWN:
		switch(event->cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_START:
			*scene = GAME;
			break;
		}
	}

	return true;
}
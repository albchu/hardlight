
#include "GUI.h"
#include <string>

using namespace std;
using namespace glm;

GUI::GUI() {
}

GUI::GUI(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

void GUI::loadMenu(const char * menuPath) {
	string imagePath;
	Image image;
	Button button;
	double x, y;

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

		addImage(image);
	}

	// load buttons
	for(int i = 0; i < numOfButtons; i++) {
		int imgPos;
		string action;

		imgPos = loader->GetInteger("buttons", string("imageNum") + to_string(i+1), 1);
		action = loader->Get("buttons", string("action") + to_string(i+1), "");
		
		button = Button(images[imgPos - 1].getPath().c_str());
		
		if(action.compare("start") == 0) {
			button.setAction(START);
		}
		else if(action.compare("quit") == 0) {
			button.setAction(QUIT);
		}

		addButton(button);
	}
}

void GUI::render(int winWidth, int winHeight, SDL_Window* window) {

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, winWidth/winHeight, 0.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 0.0f, winWidth/2.0f, winHeight/2.0f, 100.0f, 0.0f, 1.0f, 0.0f);

	for(Image i : images) {

		GLfloat x = i.getPos().x;
		GLfloat y = i.getPos().y;
		GLfloat w = i.getSize().x;
		GLfloat h = i.getSize().y;

		glBindTexture(GL_TEXTURE_2D, i.getTextureID());

		glBegin(GL_TRIANGLES);

		//first triangle
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y, 100.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x + w, y, 100.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x + w, y + h, 100.0f);

		// second triangle
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y, 100.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x, y + h, 100.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x + w, y + h, 100.0f);

		glEnd();

	}

	for(Button b : buttons) {

		GLfloat x = b.getPos().x;
		GLfloat y = b.getPos().y;
		GLfloat w = b.getSize().x;
		GLfloat h = b.getSize().y;

		glBindTexture(GL_TEXTURE_2D, b.getTextureID());

		glBegin(GL_TRIANGLES);

		//first triangle
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y, 100.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x + w, y, 100.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x + w, y + h, 100.0f);

		// second triangle
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y, 100.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x, y + h, 100.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x + w, y + h, 100.0f);

		glEnd();
	}

	SDL_GL_SwapWindow(window);
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
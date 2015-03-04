#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "Element.h"

class Scene {
private:
	vector<Element> elements;

public:
	void addElement(Element);
	void render();
}

#endif
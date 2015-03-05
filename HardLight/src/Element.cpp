
#include "Element.h"

Element::Element() {
}

Element::Element(const char* texturePath) {
}

Element::~Element() {
}

glm::vec2 Element::getPos() {
	return pos;
}

void Element::setPos(glm::vec2 newPos) {
	pos = newPos;
}
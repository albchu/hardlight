#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <glm/glm.hpp>

class Element {
private:
	glm::vec3 pos;
public:
	glm::vec3 getPos();
	void setPos(glm::vec3);
};

#endif
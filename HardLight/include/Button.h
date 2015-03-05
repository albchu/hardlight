#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Element.h"

class Button : public Element {
private:
	Action command;

public:
	Button();
	~Button();
};

#endif
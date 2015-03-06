#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Element.h"

class Button : public Element {
private:
	Action command;

public:
	Button();
	Button(const char*);
	~Button();

	void setAction(Action);

	Action getAction();
};

#endif
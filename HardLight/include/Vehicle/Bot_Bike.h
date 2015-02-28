#ifndef _BOT_BIKE_H
#define _BOT_BIKE_H

#include "Vehicle/Bike.h"
#include "AI/Bot_Controller.h"

using namespace glm;
using namespace std;

class Bot_Bike : public Bike
{

public:
	Bot_Controller* getController();
	void set_controller(Bot_Controller*);
private:
	Bot_Controller* controller;
};
#endif
#ifndef _AI_H
#define _AI_H

#include "Vehicle/BikeManager.h"
#include "Common.h"
#include "KeyMappings.h"
#include <glm/gtx/vector_angle.hpp>

class AI
{
public:
	AI(BikeManager* init_manager);//, vector<KeyMapping> init_keyMappings);
	void update_bikes();
	void update_bikes(vec3 pickup);
	void move_bikes();
//	void notify(SDL_Keycode key);
	void update_player(Player_Controller* player);
	void update_controller(Player_Controller* player);
//	void update_keyboard(Player_Controller* player);

private:
	BikeManager* bike_manager;
//	vector<KeyMapping> keyMappings;
//	vector<SDL_Keycode> keyPresses;	// The buffer that holds all keys we are notified of
};
#endif
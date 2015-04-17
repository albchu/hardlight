#ifndef _AI_H
#define _AI_H

#include "Vehicle/BikeManager.h"
#include "Common.h"
#include "KeyMappings.h"
#include <glm/gtx/vector_angle.hpp>
#include "SoundMixer.h"
#include "LoopTimer.h"
#include "Powerup/PowerupManager.h"
#include "../inih\cpp\INIReader.h"

class AI
{
public:
	AI(BikeManager* init_manager, SoundMixer* init_sfxMix, INIReader* config);//, vector<KeyMapping> init_keyMappings);
	//void update_bikes();
	void update_bikes(PowerupManager* powerup_manager);
	void move_bikes();
//	void notify(SDL_Keycode key);
	void update_player(Bike* bike);
	void update_controller(Bike* bike);
//	void update_keyboard(Player_Controller* player);

private:
	BikeManager* bike_manager;
	SoundMixer* sfxMix;
	bool channel_available; // Used to play taunt once per button press
	float avoidance_angle;
	LoopTimer* aiCalc;
};
#endif
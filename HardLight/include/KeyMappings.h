#ifndef _KEY_MAPPING_H
#define _KEY_MAPPING_H

#include <SDL.h>
#include <vector>

using namespace std;

struct KeyMapping
{
	SDL_Keycode forward;
	SDL_Keycode backward;
	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode camera_right;
	SDL_Keycode camera_left;
};

class KeyMappings
{
public:
	static vector<KeyMapping> generate_keyMappings();
};
#endif
#include "KeyMappings.h"

// Hard coded configurations for controls, we only support up to 4 players so theres no reason behind dynamically doing this
vector<KeyMapping> KeyMappings::generate_keyMappings()
{
	vector<KeyMapping> keymappings;
	KeyMapping player1;
	KeyMapping player2;
	KeyMapping player3;
	KeyMapping player4;

	//Player 1
	player1.forward = SDLK_w;
	player1.backward = SDLK_s;
	player1.left = SDLK_a;
	player1.right = SDLK_d;
	player1.camera_right = SDLK_q;
	player1.camera_left = SDLK_e;
	player1.use_powerup = SDLK_f;
	
	//Player 2
	player2.forward = SDLK_UP;
	player2.backward = SDLK_DOWN;
	player2.left = SDLK_LEFT;
	player2.right = SDLK_RIGHT;
	player2.camera_right = SDLK_RSHIFT;
	player2.camera_left = SDLK_RCTRL;
	player2.use_powerup = SDLK_DELETE;
		
	//Player 3
	player3.forward = SDLK_u;
	player3.backward = SDLK_j;
	player3.left = SDLK_h;
	player3.right = SDLK_k;
	player3.camera_right = SDLK_y;
	player3.camera_left = SDLK_i;
	player3.use_powerup = SDLK_l;
		
	//Player 4	Makes sense on numpad
	player4.forward = SDLK_5;
	player4.backward = SDLK_2;
	player4.left = SDLK_1;
	player4.right = SDLK_3;
	player4.camera_right = SDLK_4;
	player4.camera_left = SDLK_6;
	player4.use_powerup = SDLK_0;

	keymappings.push_back(player1);
	keymappings.push_back(player2);
	keymappings.push_back(player3);
	keymappings.push_back(player4);
	return keymappings;
}

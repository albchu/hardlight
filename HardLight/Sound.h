#ifndef _SOUND_H
#define _SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>


class Sound {

private:
	Mix_Music *musicOverworld;
	Mix_Chunk *sfxEngine;
	
public:
	Sound();

	void InitializeMixer();

};

#endif
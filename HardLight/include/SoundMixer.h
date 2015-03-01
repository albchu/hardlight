#ifndef _SOUND_H
#define _SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>

#include "../inih\cpp\INIReader.h"


class SoundMixer {

private:
	Mix_Music *musicOverworld;
	Mix_Chunk *sfxEngine;
	Mix_Chunk *sfxExplosion;
	Mix_Chunk *sfxIntro;
	Mix_Chunk *sfxItemPickup;
	Mix_Chunk *sfxItemUsed;

	std::vector<Mix_Music*> musicFilesList;
	std::vector<Mix_Chunk*> sfxFilesList;

	std::string pathToAudioDir;
	std::string errorSound;

	std::string musicOverworldFile;
	std::string sfxEngineFile;
	std::string sfxExplosionFile;
	std::string sfxIntroFile;
	std::string sfxItemPickupFile;
	std::string sfxItemUsedFile;
	
public:
	SoundMixer();

	bool InitializeMixer(INIReader *config);
	void CloseMixer();

	void PlayMusic(int index);
	void PlaySoundEffect(int index);
};

#endif
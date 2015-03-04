#ifndef _SOUND_H
#define _SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../inih\cpp\INIReader.h"


class SoundMixer {


private:
	Mix_Music							*musicOverworld;
	Mix_Music							*musicMenu;
	Mix_Chunk							*sfxEngine;
	Mix_Chunk							*sfxExplosion;
	Mix_Chunk							*sfxIntro;
	Mix_Chunk							*sfxItemPickup;
	Mix_Chunk							*sfxItemUsed;

	std::map<std::string, Mix_Music*>	musicFilesList;
	std::map<std::string, Mix_Chunk*>	sfxFilesList;

	std::string							pathToAudioDir;
	std::string							errorSound;

	std::string							musicOverworldFile;
	std::string							musicMenuFile;
	std::string							sfxEngineFile;
	std::string							sfxExplosionFile;
	std::string							sfxIntroFile;
	std::string							sfxItemPickupFile;
	std::string							sfxItemUsedFile;

	int musicVolume;
	int sfxVolume;

	int numChannels;
	int currentChannelIndex;

	float maxHearingRadius;

public:
	SoundMixer();

	bool	InitializeMixer(INIReader *config);
	void	CloseMixer();

	int		PlayMusic(std::string key);
	int		PlayMusic(std::string key, int volume);									// Play music at preset volume
	int		PlaySoundEffect(std::string key);
	int		PlaySoundEffect(std::string key, float distance, int timesToRepeat);	// Play sound effect based on distance from listener

	void	UpdateVolume(int previousChannelIndex, float distance);					// Adjust currently playing sfx based on new distance from listener

};

#endif
#ifndef _SOUND_H
#define _SOUND_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <Windows.h>

#include "../inih\cpp\INIReader.h"


class SoundMixer {


private:
	Mix_Music							*musicOverworld;
	Mix_Music							*musicMenu;
	Mix_Chunk							*sfxEngine;
	Mix_Chunk							*sfxExplosion;
	Mix_Chunk							*sfxIntro;
	Mix_Chunk							*randomSoundEffect;
	Mix_Chunk							*sfxPowerupReady;
	Mix_Chunk							*sfxPowerupInstant;
	Mix_Chunk							*sfxPowerupActivated;
	Mix_Chunk							*sfxPowerupNone;
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
	std::string							randomSoundEffectFile;
	std::string							sfxPowerupReadyFile;
	std::string							sfxPowerupInstantFile;
	std::string							sfxPowerupActivatedFile;
	std::string							sfxPowerupNoneFile;
	std::string							sfxItemPickupFile;
	std::string							sfxItemUsedFile;

	int musicVolume;
	double sfxVolume;

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
	bool	ClipFrom(const char* directory);
};

#endif
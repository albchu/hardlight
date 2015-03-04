#include "SoundMixer.h"

SoundMixer::SoundMixer()
{
	musicOverworld = NULL;
	musicMenu = NULL;

	sfxEngine = NULL;
	sfxExplosion = NULL;
	sfxIntro = NULL;
	sfxItemPickup = NULL;
	sfxItemUsed = NULL;

	pathToAudioDir = "../data/Audio/";
	errorSound = "errorSound.wav";

	musicVolume = -1;
	sfxVolume = -1;

	numChannels = 64;
	currentChannelIndex = 0;
}

bool SoundMixer::InitializeMixer(INIReader *config)
{
	//Get musicVolume from .ini file
	musicVolume = config->GetInteger("sound", "musicVolume", -1);

	//Get maxHearingRadius from .ini file
	maxHearingRadius = (float)config->GetReal("sound", "maxHearingRadius", 250.0f);

	//Get music file paths from the .ini file
	musicOverworldFile = pathToAudioDir + config->Get("sound", "musicOverWorldFile", errorSound);
	musicMenuFile = pathToAudioDir + config->Get("sound", "musicMenuFile", errorSound);

	sfxEngineFile = pathToAudioDir + config->Get("sound", "sfxEngineFile", errorSound);
	sfxExplosionFile = pathToAudioDir + config->Get("sound", "sfxExplosionFile", errorSound);
	sfxIntroFile = pathToAudioDir + config->Get("sound", "sfxIntroFile", errorSound);
	sfxItemPickupFile = pathToAudioDir + config->Get("sound", "sfxItemPickupFile", errorSound);
	sfxItemUsedFile = pathToAudioDir + config->Get("sound", "sfxItemUsedFile", errorSound);

	//Initialize SDL mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
	{ 
		std::cout << "Problem initializing SDL_Mixer. SDL_Mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	//Load music 
	musicOverworld = Mix_LoadMUS( musicOverworldFile.c_str() ); 
	if( musicOverworld == NULL ) 
	{
		std::cout << "Failed to load background music: " << musicOverworldFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false; 
	} 
	musicMenu = Mix_LoadMUS( musicMenuFile.c_str() ); 
	if( musicMenu == NULL ) 
	{
		std::cout << "Failed to load menu music: " << musicMenuFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false; 
	} 
	//Load sound effects 
	sfxEngine = Mix_LoadWAV( sfxEngineFile.c_str() );
	if( sfxEngine == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxEngineFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxExplosion = Mix_LoadWAV( sfxExplosionFile.c_str() ); 
	if( sfxExplosion == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxExplosionFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxIntro = Mix_LoadWAV( sfxIntroFile.c_str() );
	if( sfxIntro == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxIntroFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxItemPickup = Mix_LoadWAV( sfxItemPickupFile.c_str() ); 
	if( sfxItemPickup == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxItemPickupFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxItemUsed = Mix_LoadWAV( sfxItemUsedFile.c_str() );
	if( sfxItemUsed == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxItemUsedFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	// Add pointers to file list
	musicFilesList["musicOverworld"] = musicOverworld;
	musicFilesList["musicMenu"] = musicMenu;
	sfxFilesList["sfxEngine"] = sfxEngine;
	sfxFilesList["sfxExplosion"] = sfxExplosion;
	sfxFilesList["sfxIntro"] = sfxIntro;
	sfxFilesList["sfxItemPickUp"] = sfxItemPickup;
	sfxFilesList["sfxItemUsed"] = sfxItemUsed;

	Mix_AllocateChannels(64);
	printf("number of channels is now : %d\n", Mix_AllocateChannels(-1));
	return true;
}

void SoundMixer::CloseMixer()
{
	//Free the music 
	Mix_FreeMusic( musicOverworld ); 
	Mix_FreeMusic( musicMenu );
	musicOverworld = NULL;
	musicMenu = NULL;

	//Free the sound effects 
	Mix_FreeChunk( sfxEngine ); 
	Mix_FreeChunk( sfxExplosion ); 
	Mix_FreeChunk( sfxIntro ); 
	Mix_FreeChunk( sfxItemPickup ); 
	Mix_FreeChunk( sfxItemUsed ); 
	sfxEngine = NULL;
	sfxExplosion = NULL;
	sfxIntro = NULL;
	sfxItemPickup = NULL;
	sfxItemUsed = NULL;

	//Quit SDL subsystems
	Mix_Quit();
}

int SoundMixer::PlayMusic(std::string key)
{
	int errorCode;
	
	Mix_VolumeMusic(musicVolume);
	//If there is no music playing 
	if( Mix_PlayingMusic() == 0 )
	{ 
		//Play the music 
		errorCode = Mix_PlayMusic( musicFilesList[key], -1 );
	} 
	//If music is being played 
	else 
	{ 
		//If the music is paused 
		if( Mix_PausedMusic() == 1 ) 
		{ 
			//Resume the music 
			Mix_ResumeMusic();
		} 
		//If the music is playing 
		else 
		{ 
			//Pause the music 
			Mix_PauseMusic(); 
		} 
	}
	return errorCode;
}

int SoundMixer::PlayMusic(std::string key, int volume)
{
	int errorCode;
	
	Mix_VolumeMusic(volume);
	//If there is no music playing 
	if( Mix_PlayingMusic() == 0 )
	{ 
		//Play the music 
		errorCode = Mix_PlayMusic( musicFilesList[key], -1 );
		printf("sdsd0 if success: %d\n", errorCode);
	} 
	//If music is being played 
	else 
	{ 
		//If the music is paused 
		if( Mix_PausedMusic() == 1 ) 
		{ 
			//Resume the music 
			Mix_ResumeMusic();
		} 
		//If the music is playing 
		else 
		{ 
			//Pause the music 
			Mix_PauseMusic(); 
		} 
	}
	return errorCode;
}

int SoundMixer::PlaySoundEffect(std::string key)
{
	int previousChannelIndex = currentChannelIndex;
	Mix_Volume(currentChannelIndex, 128
		);
	int errorCode = Mix_PlayChannel(-1, sfxFilesList[key], 0);
	if( errorCode == -1)
	{
		printf("Channel: %d\n", errorCode);
		return errorCode;
	}
	currentChannelIndex++;
	if (currentChannelIndex > 63)
		currentChannelIndex = 0;

	// Return the channel the sound was played on
	return previousChannelIndex;
}

int SoundMixer::PlaySoundEffect(std::string key, float distance, int timesToRepeat)
{
	int previousChannelIndex = currentChannelIndex;
	// Calculate volume of sound effect based on distance from entity
	float volumeRatio = 1.0f / ( 1.0f + abs(distance/maxHearingRadius) );
	sfxVolume = (int)(volumeRatio * 128.0f);
	/*float volumeRatio = maxHearingRadius - distance / maxHearingRadius;
	sfxVolume = (int)(volumeRatio * maxHearingRadius);*/
	Mix_Volume(currentChannelIndex, (int)sfxVolume);

	//printf("volumeRatio: %f\n", volumeRatio);
	//printf("sfxVolume: %f\n", sfxVolume);
	

	// Play the sound effect on the first avaliable channel
	int errorCode = Mix_PlayChannel(currentChannelIndex, sfxFilesList[key], timesToRepeat);
	if( errorCode == -1)
	{
		printf("Channel: %d\n", errorCode);
		return errorCode;
	}
	currentChannelIndex++;
	if (currentChannelIndex > 63)
		currentChannelIndex = 0;

	// Return the channel the sound was played on
	return previousChannelIndex;
}

void SoundMixer::UpdateVolume(int previousChannelIndex, float distance)
{
	float volumeRatio = 1.0f / ( 1.0f + abs(distance/maxHearingRadius) );
	sfxVolume = (int)(volumeRatio * 128);
	/*float volumeRatio = maxHearingRadius - distance / maxHearingRadius;
	sfxVolume = (int)(volumeRatio * maxHearingRadius);*/
	Mix_Volume(previousChannelIndex, (int)sfxVolume);
}


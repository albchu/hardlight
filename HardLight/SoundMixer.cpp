#include "SoundMixer.h"

SoundMixer::SoundMixer()
{
	musicOverworld = NULL;
	musicMenu = NULL;

	sfxEngine = NULL;
	sfxExplosion = NULL;
	sfxIntro = NULL;
	sfxPowerupReady = NULL;
	sfxPowerupInstant = NULL;
	sfxPowerupActivated = NULL;
	sfxPaused = NULL;
	sfxUnpaused = NULL;
	
	pathToAudioDir = "../data/Audio/";
	errorSound = "errorSound.wav";

	musicVolume = -1;
	sfxVolume = -1;

	numChannels = 65;
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
	sfxPowerupReadyFile = pathToAudioDir + config->Get("sound", "sfxPowerupReadyFile", errorSound);
	sfxPowerupInstantFile = pathToAudioDir + config->Get("sound", "sfxPowerupInstantFile", errorSound);
	sfxPowerupActivatedFile = pathToAudioDir + config->Get("sound", "sfxPowerupActivatedFile", errorSound);
	sfxPowerupNoneFile = pathToAudioDir + config->Get("sound", "sfxPowerupNoneFile", errorSound);
	sfxPausedFile = pathToAudioDir + config->Get("sound", "sfxPausedFile", errorSound);
	sfxUnpausedFile = pathToAudioDir + config->Get("sound", "sfxUnpausedFile", errorSound);


	//Set random sound effect to be the error sound initially
	randomSoundEffectFile = pathToAudioDir + errorSound;

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

	sfxPowerupReady = Mix_LoadWAV( sfxPowerupReadyFile.c_str() ); 
	if( sfxPowerupReady == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxPowerupReadyFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxPowerupInstant = Mix_LoadWAV( sfxPowerupInstantFile.c_str() );
	if( sfxPowerupInstant == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxPowerupInstantFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxPowerupActivated = Mix_LoadWAV( sfxPowerupActivatedFile.c_str() );
	if( sfxPowerupActivated == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxPowerupActivatedFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	
	sfxPowerupNone = Mix_LoadWAV( sfxPowerupNoneFile.c_str() );
	if( sfxPowerupNone == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxPowerupNoneFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxPaused = Mix_LoadWAV( sfxPausedFile.c_str() );
	if( sfxPaused == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxPausedFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	sfxUnpaused = Mix_LoadWAV( sfxUnpausedFile.c_str() );
	if( sfxUnpaused == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxUnpausedFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	// Add pointers to file list
	musicFilesList["musicOverworld"] = musicOverworld;
	musicFilesList["musicMenu"] = musicMenu;
	sfxFilesList["sfxEngine"] = sfxEngine;
	sfxFilesList["sfxExplosion"] = sfxExplosion;
	sfxFilesList["sfxIntro"] = sfxIntro;
	sfxFilesList["sfxPowerupReady"] = sfxPowerupReady;
	sfxFilesList["sfxPowerupInstant"] = sfxPowerupInstant;
	sfxFilesList["sfxPowerupActivated"] = sfxPowerupActivated;
	sfxFilesList["sfxPowerupNone"] = sfxPowerupNone;
	sfxFilesList["sfxPaused"] = sfxPaused;
	sfxFilesList["sfxUnpaused"] = sfxUnpaused;

	Mix_AllocateChannels(numChannels);
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
	Mix_FreeChunk( sfxPowerupReady ); 
	Mix_FreeChunk( sfxPowerupInstant ); 
	Mix_FreeChunk( sfxPowerupActivated ); 
	Mix_FreeChunk( sfxPaused );
	Mix_FreeChunk( sfxUnpaused );
	sfxEngine = NULL;
	sfxExplosion = NULL;
	sfxIntro = NULL;
	sfxPowerupReady = NULL;
	sfxPowerupInstant = NULL;
	sfxPowerupActivated = NULL;
	sfxPaused = NULL;
	sfxUnpaused = NULL;

	//Quit SDL subsystems
	Mix_Quit();
}

int SoundMixer::PlayMusic(std::string key)
{
	int errorCode = -1;

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
	int errorCode = -1;

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
	Mix_Volume(currentChannelIndex, 128);
	int errorCode = Mix_PlayChannel(currentChannelIndex, sfxFilesList[key], 0);
	if( errorCode == -1)
	{
		printf("Channel: %d\n", errorCode);
		return errorCode;
	}
	do
	{
		currentChannelIndex++;
	} while (Mix_Playing(currentChannelIndex) == 1);
	if (currentChannelIndex > 63)
		currentChannelIndex = 0;

	// Return the channel the sound was played on
	return previousChannelIndex;
}

int SoundMixer::PlaySoundEffect(std::string key, float distance, int timesToRepeat)
{
	if (distance > maxHearingRadius) return -1;
	int previousChannelIndex = currentChannelIndex;
	// Calculate volume of sound effect based on distance from entity
	float volumeRatio = (distance/maxHearingRadius);
	volumeRatio = 1 - volumeRatio;
	volumeRatio *= volumeRatio;
	sfxVolume = (int)(volumeRatio * 128.0f);
	Mix_Volume(currentChannelIndex, (int)sfxVolume);
	/*
	printf("distance: %f\n", distance);
	printf("volumeRatio: %f\n", volumeRatio);
	printf("sfxVolume: %f\n", sfxVolume);
	*/

	// Play the sound effect on the first avaliable channel
	int errorCode = Mix_PlayChannel(currentChannelIndex, sfxFilesList[key], timesToRepeat);
	if( errorCode == -1)
	{
		printf("Channel: %d\n", errorCode);
		return errorCode;
	}
	do
	{
		currentChannelIndex++;
	} while (Mix_Playing(currentChannelIndex) == 1);
	if (currentChannelIndex > 63)
		currentChannelIndex = 0;

	// Return the channel the sound was played on
	return previousChannelIndex;
}

bool SoundMixer::ClipFrom(const char* directory)
{
	char searchPath[200];
	wchar_t* wbuff;
	char* cbuff;
	std::string path;
	std::vector<std::string> allDirectoryFiles;

	sprintf_s(searchPath, "%s*.wav", directory);
	WIN32_FIND_DATA fd;

	int size = MultiByteToWideChar(CP_UTF8, 0, searchPath, -1, NULL, 0);
	wbuff = new wchar_t[size];
	MultiByteToWideChar(CP_UTF8, 0, searchPath, -1, wbuff, size);

	// Parse all the files in the directory specified by the function argument
	HANDLE handle = ::FindFirstFile(wbuff, &fd);
	std::cout << "Choosing sound effect file from the current folder: " << std::endl;
	if(handle != INVALID_HANDLE_VALUE) { 
		do { 

			if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {

				size = WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, NULL, 0,  NULL, NULL);
				cbuff = new char[size];
				WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, &cbuff[0], size, NULL, NULL);


				std::string dirString = std::string(directory);
				std::string filename = std::string(cbuff);

				// Push back the relative path to the filename to the vector
				allDirectoryFiles.push_back(dirString + filename);
				std::cout << filename << std::endl;
			}
		}while(::FindNextFile(handle, &fd));
		::FindClose(handle); 
	}
	
	// Choose file from vector of files
	path = allDirectoryFiles[rand() % allDirectoryFiles.size()];

	// Load selected file as a SDL_mixer object
	randomSoundEffect = Mix_LoadWAV( path.c_str() );
	if( randomSoundEffect == NULL)
	{
		std::cout << "Failed to load sound effect: " << path << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}
	std::cout << "The selected sound effect is" << path << std::endl;

	// Play selected file
	//if( Mix_Playing(64) == 1)
	//{	
	//	printf("Random sound currently playing");
	//	return false;
	//}
	Mix_Volume(64, 128);
	int errorCode = Mix_PlayChannel(64, randomSoundEffect, 0);
	if( errorCode == -1)
	{
		printf("Channel: %d\n", errorCode);
		return false;
	}

	return true;
}

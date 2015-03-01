#include "SoundMixer.h"

SoundMixer::SoundMixer()
{
	musicOverworld = NULL;
	sfxEngine = NULL;
	sfxExplosion = NULL;
	sfxIntro = NULL;
	sfxItemPickup = NULL;
	sfxItemUsed = NULL;

	pathToAudioDir = "../data/Audio/";
	errorSound = "errorSound.wav";
}

void SoundMixer::InitializeMixer(INIReader *config)
{
	musicOverworldFile = pathToAudioDir + config->Get("sound", "musicOverWorldFile", errorSound);
	sfxEngineFile = pathToAudioDir + config->Get("sound", "sfxEngineFile", errorSound);
	sfxExplosionFile = pathToAudioDir + config->Get("sound", "sfxExplosionFile", errorSound);
	sfxIntroFile = pathToAudioDir + config->Get("sound", "sfxIntroFile", errorSound);
	sfxItemPickupFile = pathToAudioDir + config->Get("sound", "sfxItemPickupFile", errorSound);
	sfxItemUsedFile = pathToAudioDir + config->Get("sound", "sfxItemUsedFile", errorSound);

	//Initialize SDL mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
	{ 
		std::cout << "Problem initializing SDL_Mixer. SDL_Mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}

	//Load music 
	musicOverworld = Mix_LoadMUS( musicOverworldFile.c_str() ); 
	if( musicOverworld == NULL ) 
	{
		std::cout << "Failed to load background music: " << musicOverworldFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit; 
	} 
	//Load sound effects 
	sfxEngine = Mix_LoadWAV( sfxEngineFile.c_str() );
	if( sfxEngine == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxEngineFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}

	sfxExplosion = Mix_LoadWAV( sfxExplosionFile.c_str() ); 
	if( sfxExplosion == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxExplosionFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}

	sfxIntro = Mix_LoadWAV( sfxIntroFile.c_str() );
	if( sfxIntro == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxIntroFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}
	
	sfxItemPickup = Mix_LoadWAV( sfxItemPickupFile.c_str() ); 
	if( sfxItemPickup == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxItemPickupFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}

	sfxItemUsed = Mix_LoadWAV( sfxItemUsedFile.c_str() );
	if( sfxItemUsed == NULL ) 
	{ 
		std::cout << "Failed to load sound effect: " << sfxItemUsedFile << " ! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}

	// Add pointers to file list
	musicFilesList.push_back(musicOverworld);
	sfxFilesList.push_back(sfxEngine);
	sfxFilesList.push_back(sfxExplosion);
	sfxFilesList.push_back(sfxIntro);
	sfxFilesList.push_back(sfxItemPickup);
	sfxFilesList.push_back(sfxItemUsed);
}

void SoundMixer::CloseMixer()
{
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

	//Free the music 
	Mix_FreeMusic( musicOverworld ); 
	musicOverworld = NULL;

	//Quit SDL subsystems
	Mix_Quit();
}

void SoundMixer::PlayMusic(int index)
{
	//If there is no music playing 
	if( Mix_PlayingMusic() == 0 )
	{ 
		//Play the music 
		Mix_PlayMusic( musicFilesList[index], -1 );
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
}

void SoundMixer::PlaySoundEffect(int index)
{
	Mix_PlayChannel(-1, sfxFilesList[index], 0);
}


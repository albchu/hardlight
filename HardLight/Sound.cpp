#include "Sound.h"

Sound::Sound()
{
	musicOverworld = NULL;
	sfxEngine = NULL;
}

void Sound::InitializeMixer()
{
	//Initialize SDL mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
	{ 
		std::cout << "Problem initializing SDL_Mixer. SDL_Mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}

	//Load music 
	musicOverworld = Mix_LoadMUS( "../data/musicOverworld.wav" ); 
	if( musicOverworld == NULL ) 
	{
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit; 
	} 
	
	//Load sound effects 
	sfxEngine = Mix_LoadWAV( "../data/sfxEngine.wav" ); 
	if( sfxEngine == NULL ) 
	{ 
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}
}
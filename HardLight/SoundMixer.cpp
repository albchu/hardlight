#include "SoundMixer.h"

SoundMixer::SoundMixer()
{
	musicOverworld = NULL;
	sfxEngine = NULL;
}

void SoundMixer::InitializeMixer()
{
	//Initialize SDL mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) 
	{ 
		std::cout << "Problem initializing SDL_Mixer. SDL_Mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}

	//Load music 
	musicOverworld = Mix_LoadMUS( "../data/Audio/musicOverworld.wav" ); 
	if( musicOverworld == NULL ) 
	{
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit; 
	} 
	
	//Load sound effects 
	sfxEngine = Mix_LoadWAV( "../data/Audio/sfxEngine.wav" ); 
	if( sfxEngine == NULL ) 
	{ 
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit;
	}
}

void SoundMixer::CloseMixer()
{

}

void SoundMixer::PlayBackgroundMusic()
{

}
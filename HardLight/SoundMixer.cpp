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
void SoundMixer::PlaySoundEffect()
{
	Mix_PlayChannel(-1, sfxEngine, 0);
}
void SoundMixer::PlayBackgroundMusic()
{
	//If there is no music playing 
	if( Mix_PlayingMusic() == 0 )
	{ 
		//Play the music 
		Mix_PlayMusic( musicOverworld, -1 );
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


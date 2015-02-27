#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;

int Control( int argc, char *argv[] ){
        
        SDL_Window* window = NULL;
		SDL_Surface* screenSurface = NULL;
        int quit = 0;
        SDL_Event e;
		SDL_GameController* controller = NULL;

        /* Initialise SDL */
        if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0){
            fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
            exit( -1 );
        }else{ 
			window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
			if( window == NULL ) { 
				printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
			}else { //Get window surface screen
			 screenSurface = SDL_GetWindowSurface( window );
				for (int i = 0; i < SDL_NumJoysticks(); ++i) {
					if (SDL_IsGameController(i)) {
						controller = SDL_GameControllerOpen(i);
						if (controller) {
						break;
						} else {
						fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
						}
					}
				}
			}
		}

        /* Loop until an SDL_QUIT event is found */
        while( !quit ){

            /* Poll for events */
            while( SDL_PollEvent( &e ) != 0){
                
                switch( e.type ){
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
					case SDL_CONTROLLERAXISMOTION:
						printf("Left x = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX));
						printf("Left Y = %i\n", SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY));

                    case SDL_QUIT:
                        quit = 1;
                        break;

                    default:
                        break;
                }

            }

        }
		return 0;
}
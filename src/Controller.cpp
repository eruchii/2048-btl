#include "Controller.h"
#include <SDL2/SDL.h>
#include <stdio.h>

extern SDL_GameController* gGameController = NULL;
extern SDL_Haptic* gControllerHaptic = NULL;
extern bool controllerConnected = false;

void initController(){
	if( SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return;
	}
	if( SDL_NumJoysticks() < 1 ){
			printf( "Warning: No joysticks connected!\n" );
		}
		else{
			SDL_GameControllerAddMappingsFromFile("mapping.txt");
			for(int i = 0 ; i < SDL_NumJoysticks() ; i++){
				if(SDL_IsGameController(i)){
					gGameController = SDL_GameControllerOpen(i);
					gControllerHaptic = SDL_HapticOpenFromJoystick( SDL_GameControllerGetJoystick(gGameController) );
					if( gControllerHaptic == NULL ){
						printf( "Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError() );
					}
					else{
						if( SDL_HapticRumbleInit( gControllerHaptic ) < 0 ){
							printf( "Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError() );
						}
					}
					break;
				}
				if( gGameController == NULL ){
					printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
				}
				else controllerConnected = true;
			}
		}
}
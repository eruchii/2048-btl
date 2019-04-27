#ifndef Controller_h
#define Controller_h

#include <SDL.h>

extern SDL_GameController* gGameController;
extern SDL_Haptic* gControllerHaptic;
extern bool controllerConnected;

void initController();

#endif
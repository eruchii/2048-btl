#ifndef Window_h
#define Window_h

#include <SDL2/SDL.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;

extern bool InitSDL();
extern void CloseSDL();

extern const SDL_Color BLACK;
extern const SDL_Color WHITE;


#endif
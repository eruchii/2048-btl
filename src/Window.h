#ifndef Window_h
#define Window_h

#include <SDL.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;

extern bool InitSDL();
extern void CloseSDL();

extern const SDL_Color BLACK;
extern const SDL_Color WHITE;

extern SDL_Color Color_Mix(const SDL_Color &color1, const SDL_Color &color2, double weight);


#endif
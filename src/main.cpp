#include "Window.h"
#include "Grid.h"
#include "Controller.h"
#include "Render.h"
#include <stdio.h>
#include "Texture.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "Button.h"
using namespace std;

#define DPAD_UP 11
#define DPAD_DOWN 12
#define DPAD_LEFT 13
#define DPAD_RIGHT 14
#define L1 9
#define R1 10
#define START 4 // SHARE on Dualshock 4
#define SELECT 6 // OPTIONS on dualshock 4

Game game;

Button *newGameBtn = NULL;

void globalUpdate(){
	g_render.setDrawColor(WHITE);
	g_render.clear();
	game.update();
	newGameBtn -> render();
	g_render.present();
}

int main(int argv, char** args){
    if(!InitSDL()) return 1;
	initController();
	g.init();
	Texture num;
	TTF_Font *font = NULL;
	
	game.init();
	g_render.init(g_renderer);
	newGameBtn = new Button("New game", []{g.init(); globalUpdate();});
    newGameBtn -> setXY (130 - 15, 30);

	globalUpdate();
	
	SDL_Event e;
	bool quit = 0;
	while(!quit){
		while(SDL_PollEvent(&e)) {
			newGameBtn->handleEvent(e);
			if(e.type == SDL_QUIT){
				quit = 1;
			}
			else if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
				case SDLK_UP:
					g.gridMove(UP);
					break;
				case SDLK_RIGHT:
					g.gridMove(RIGHT);
					break;
				case SDLK_DOWN:
					g.gridMove(DOWN);
					break;
				case SDLK_LEFT:
					g.gridMove(LEFT);
					break;
				}
				globalUpdate();

			}
			else if(e.type == SDL_CONTROLLERBUTTONDOWN){
				printf("%d\n", e.cbutton.button);
				switch(e.cbutton.button) {
				case DPAD_UP:
					g.gridMove(UP);
					break;
				case DPAD_RIGHT:
					g.gridMove(RIGHT);
					break;
				case DPAD_DOWN:
					g.gridMove(DOWN);
					break;
				case DPAD_LEFT:
					g.gridMove(LEFT);
					break;
				case START:
					g.init();
					break;
				case SELECT:
					g.debug1();
					break;
				case L1:
					g.debug2();
					break;
				case R1:
					g.debug3();
					break;
				}
				int gMaxValue = g.getMaxValue();
				if(g.currentMaxValue < gMaxValue){
					int msec = gMaxValue - g.currentMaxValue;
					if(msec < 200) msec = 200;
					if(msec > 700) msec = 700;
					if( SDL_HapticRumblePlay( gControllerHaptic, 0.4, msec ) != 0 ){
						printf( "Warning: Unable to play rumble! %s\n", SDL_GetError() );
					}
					g.currentMaxValue = gMaxValue;
				}
				globalUpdate();

			}
			else if(e.type == SDL_CONTROLLERDEVICEADDED){
				initController();
			}
			else if(e.type == SDL_CONTROLLERDEVICEREMOVED){
				printf("Controller removed!");
			}
		}
		SDL_Delay(10);
	}
	CloseSDL();
}
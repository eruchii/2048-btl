#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>
#include "Window.h"
#include "Font.h"
#include "Render.h"
#include "Texture.h"
#include "Grid.h"
#include <vector>

void calculatePosition(int row, int col, int *pX, int *pY);
struct Tile{
    int value;
    SDL_Color bgColor;
    SDL_Color textColor;
    int x;
    int y;
};

class Game{
    public:
        Game();
        ~Game();
        void update();
        void init();
    private:    
        void buildHolder();
        void buildDetail();
        void gameOverScreen();
        void ScoreBoard();
        void newGameButton();
        Font font;
};

#endif

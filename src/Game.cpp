#include "Render.h"
#include "Texture.h"
#include "Game.h"
#include <math.h>
#include "Font.h"
#include <string>
#include "Button.h"

const int ScoreboardW = 250;
const int ScoreboardH = 80;
const int tileWidth = 100;
const int spaceWidth = 15;
const int gX = 130;
const int gY = 150;
void calculatePosition(int row, int col, int *pX, int *pY){
	*pX = gX + col * (tileWidth + spaceWidth);
	*pY = gY + row * (tileWidth + spaceWidth);
}

const SDL_Color BLANK_SQUARE_COLOR = {205, 193, 181};
const SDL_Color gridColor[20] = {
    WHITE,
    {238,238,218},
    {237,224,200},
    {242,177,121},
    {245,149,99},
    {246,124,95},
    {246,94,59},
    {237,207,114},
    {237,204,97},
    {237,200,80},
    {237,197,63},
    {122,0,98},
    {160, 53, 70},
    {58, 163, 163}  
};

Game::Game(){

};

Game::~Game(){

};

void Game::init(){
}


void Game::ScoreBoard(){
    Font font;  
    font.init("ClearSans-Bold.ttf", 35); 
    string s;
    s = "Score : ";
    s = s + std::to_string(g.score);
    Texture SB, text;
    SB.createBlank(ScoreboardW, ScoreboardH , SDL_TEXTUREACCESS_TARGET);
	SB.enableAlpha();
    SDL_Color colorSB = {187, 173, 160, 255};
    g_render.setTarget(SB.sdl_texture());
    g_render.setDrawColor(colorSB);
    g_render.clear();
    text.loadText(&font, s.c_str(), WHITE);
    text.render((ScoreboardW - text.width()) / 2,(ScoreboardH - text.height()) / 2);
    g_render.setTarget(NULL);
    SB.render(340, 30);
    font.free();
}

void Game::update(){
    int gSize = g.gridSize();
    int mainSize = gSize * (tileWidth + spaceWidth) + spaceWidth;
    Font font;   
    g_render.setDrawColor(WHITE);
    g_render.clear();
    
    ScoreBoard();
    g_render.setDrawColor(0xBB, 0xAD, 0xA0);
	g_render.fillRect(gX-spaceWidth, gY-spaceWidth, mainSize , mainSize);
    
    Texture holder;
	holder.createBlank(tileWidth, tileWidth, SDL_TEXTUREACCESS_TARGET);
	holder.enableAlpha();
	g_render.setTarget(holder.sdl_texture());
	g_render.setDrawColor(238, 228, 218, static_cast<int>(0.35 * 255));
	g_render.clear();
	g_render.setTarget(nullptr);

	for(int row = 0; row < gSize; row++) {
		for(int col = 0; col < gSize; col++) {
			holder.render(gX + col * (tileWidth + spaceWidth),	gY + row * (tileWidth + spaceWidth));
		}
	}

    font.init("ClearSans-Medium.ttf", 20);
    for(int i = 0 ; i < gSize ; i++){
        for(int j = 0 ; j < gSize; j++){
            int x, y;
            calculatePosition(i, j, &x, &y);
            if(g.grid[i][j] != 0){
                g_render.setDrawColor(gridColor[(int)log2(g.grid[i][j])]);
                g_render.fillRect(x, y, tileWidth, tileWidth);
                Texture numTexture;
                SDL_Color textColor;
                if(g.grid[i][j] <= 4){ textColor = {140, 131 , 124, 255};}
                else textColor = WHITE;
                if(g.grid[i][j] <= 10){
                    font.init("ClearSans-Medium.ttf", 45);
                } else if(g.grid[i][j] <= 100){
                    font.init("ClearSans-Medium.ttf", 40);
                } else if(g.grid[i][j] <= 1000){
                    font.init("ClearSans-Medium.ttf", 35);
                } else{
                    font.init("ClearSans-Medium.ttf", 30);
                };

                numTexture.loadText(&font, std::to_string(g.grid[i][j]).c_str(), textColor);
                numTexture.render(x + (tileWidth - numTexture.width()) / 2, y + (tileWidth - numTexture.height()) / 2);
                numTexture.free();
            }
            else{
                g_render.setDrawColor(BLANK_SQUARE_COLOR);
                g_render.fillRect(x, y, tileWidth, tileWidth);
            }
        }
    }   
    if(g.gameOver()) {
		Texture mask;
		mask.createBlank(mainSize, mainSize, SDL_TEXTUREACCESS_TARGET);
		mask.enableAlpha();
		g_render.setTarget(mask.sdl_texture());
		g_render.setDrawColor(238, 228, 218, static_cast<int>(0.5 * 255));
		g_render.clear();

        Texture gameOverText;
        font.init("ClearSans-Bold.ttf", 50); 
        gameOverText.loadText(&font, "Game Over", { 0x77, 0x6E, 0x65, 0xFF });
		gameOverText.render(
			(mainSize - gameOverText.width()) / 2,
			(mainSize - gameOverText.height()) / 2);
		g_render.setTarget(nullptr);
		mask.render(gX - spaceWidth, gY - spaceWidth);
	}
    font.free();
}
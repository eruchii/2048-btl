#ifndef Grid_h
#define Grid_h

#include <iostream>
#include <vector>
#include <algorithm>  
#include <conio.h>
#include <time.h>

using namespace std;

enum Dir{
    UP, LEFT, DOWN, RIGHT
};

struct Coordinator{
    int row, col;
    Coordinator(int _x, int _y){
        row = _x;
        col = _y;
    }
};


class Grid{
    public: 
        Grid();
        ~Grid();
        void init();
        bool gameOver() { return g_gameover;};
        void printVector(vector<int> v);
        void gridMove(Dir dir);
       
        int score;
        int highscore;
        int currentMaxValue = 0;
        int getMaxValue();
        int gridSize(){return gsize;};
        int grid[10][10];
        
        void debug1();
        void debug2();
        void debug3();
    private:
        bool g_gameover = false;
        int gsize = 4;
        
        vector<Coordinator> getAvailableCells();
        void addRandom();
        void removeZero(vector<int> &v);
        int merge(vector<int> &v);
        bool moveAvailable();
};

extern Grid g;

#endif
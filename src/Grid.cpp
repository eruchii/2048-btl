#include <iostream>
#include <vector>
#include <algorithm>  
#include <conio.h>
#include <time.h>
#include "Grid.h"
#include <cstring>
using namespace std;

Grid g;

Grid::Grid(){
}

Grid::~Grid(){
}

void Grid::init(){
	memset(grid, 0, sizeof(grid));
    highscore = max(score, highscore);
	score = 0;
    addRandom();
	addRandom();
    currentMaxValue = getMaxValue();
    g_gameover = false;
}

vector<Coordinator> Grid::getAvailableCells(){
    vector<Coordinator> v;
    for(int i = 0 ; i < gsize ; i++){
        for(int j = 0 ; j < gsize ; j++){
            if(grid[i][j] == 0) v.push_back(Coordinator(i,j));
        }
    }
    return v;
}

void Grid::addRandom(){
    auto v = getAvailableCells();
	if(v.size() == 0) return;
	int index = rand() % v.size();
	int value = (rand() % 10000) < 9000 ? 2 : 4;
	grid[v[index].row][v[index].col] = value;
}
bool Grid::moveAvailable(){
    for(int i = 0 ; i < gsize ; i++){
        for(int j = 0 ; j < gsize ; j++){
            if(grid[i][j] == 0) return true;
        }
    }
    for(int i = 0 ; i < gsize-1 ; i++){
        for(int j = 0 ; j < gsize ; j++){
            if(grid[i][j] == grid[i+1][j]) return true;
        }
    }
    for(int i = 0 ; i < gsize ; i++){
        for(int j = 0 ; j < gsize-1 ; j++){
            if(grid[i][j] == grid[i][j+1]) return true;
        }
    }
    return false;
}

void Grid::removeZero(vector<int> &v){
    for(int i = 0 ; i < v.size() ; i++){
        if(v[i] == 0){
            v.erase(v.begin()+i);
            i--;
        }
    }
    while(v.size() < gsize) v.push_back(0);
}

int Grid::merge(vector<int> &v){
    int merged = 0;
    for(int i = 0 ; i < gsize-1 ; i++){
            if(v[i] == v[i+1] && v[i]!=0){
                v[i] += v[i+1];
                v[i+1] = 0;
                merged += v[i];
            }
    }
    return merged;
};

void Grid::printVector(vector<int> v){
    for(int i = 0 ; i < v.size() ; i++) cout << v[i] << " ";
    cout << endl;
}

void Grid::gridMove(Dir dir){
    if(g_gameover){
        return;
    }
    vector< vector<int> > v;
    v.assign(gsize, vector<int>());
    for(int i = 0 ; i < gsize ; i++){
        for(int j = 0 ; j < gsize ; j++){
            if(dir % 2 != 0) v[i].push_back(grid[i][j]); else v[i].push_back(grid[j][i]);
        }
        if(dir >= 2) reverse(v[i].begin(), v[i].end());
        removeZero(v[i]);
        score += merge(v[i]);
        removeZero(v[i]);
        if(dir >= 2) reverse(v[i].begin(), v[i].end());
        for(int j = 0 ; j < gsize ; j++){
            if(dir % 2 != 0) grid[i][j] = v[i][j]; else grid[j][i] = v[i][j];
        }
    }
    if(moveAvailable()){
        addRandom();
    }
    else g_gameover = true;
}

void Grid::debug1(){
    g_gameover = true;
}

void Grid::debug2(){
    score = score * 10;
}

void Grid::debug3(){
    auto v = getAvailableCells();
	if(v.size() == 0) return;
	int index = rand() % v.size();
	int value = getMaxValue() * 2;
	grid[v[index].row][v[index].col] = value;
}

int Grid::getMaxValue(){
    int vMax = 0;
    for(int i = 0 ; i < gsize ; i++){
        for(int j = 0 ; j < gsize ; j++){
            if(vMax < grid[i][j]) vMax = grid[i][j];
        }
    }
    return vMax;
}
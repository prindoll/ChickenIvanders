#pragma once
#include "Function.h"
#include "RenderWindow.h"


#define WIDTH_DAME 49
#define HEIGHT_DAME 41

class Updame : public RenderWindow {
public:
    Updame();
    ~Updame();
    void set_is_move(const bool& x) { is_move = x; }
    bool get_is_move() { return is_move; }
    void set_clip();
    void Show(SDL_Renderer* screen);
    void HandleUpdame();
    SDL_Rect GetFrame();
    
private:
    bool is_move;
    SDL_Rect clip[25];
    int frame;

    
};
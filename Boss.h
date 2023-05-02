#pragma once
#include <vector>
#include "Function.h"
#include "RenderWindow.h"




#define WIDTH_BOSS 200
#define HEIGHT_BOSS 117


class Boss : public RenderWindow {
public:
    Boss();
    ~Boss();

    void set_x_val(const int& Xval) { x_val = Xval; }
    void set_y_val(const int& Yval) { y_val = Yval; }
    int get_x_val()const { return x_val; }
    int get_y_val()const { return y_val; }

    void Move();
    void Show(SDL_Renderer* screen);
    void set_clips();
    SDL_Rect GetFrame();


    void set_heart(const float& Heart) { heart = Heart; }
    float get_heart()const { return heart; }
    void show_heart_boss(SDL_Renderer* screen, int x, int y, int w, int h);
    void setBoss();
    void Delete();
private:
    float heart;
   

    int x_val;
    int y_val;

    int left;
    int right;
    int up;
    int down;
    int frame;
    SDL_Rect clip[10];
};


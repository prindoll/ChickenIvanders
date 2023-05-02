#pragma once




#include <vector>
#include "Function.h"
#include "RenderWindow.h"
#include "Bullet.h"



#define WIDTH_CHICKEN 75
#define HEIGHT_CHICKEN 68

class Chicken : public RenderWindow {
public:
    Chicken();
    ~Chicken();

    void set_x_val(const int& Xval) { x_val = Xval; }
    void set_y_val(const int& Yval) { y_val = Yval; }
    int get_x_val()const { return x_val; }
    int get_y_val()const { return y_val; }

    void Move();
    void Move1();
    void Show(SDL_Renderer* screen);
    void set_clip();
    void set_heart(const int& x) { heart = x; }
    int get_heart() { return heart; }
    SDL_Rect GetFrame();
private:
    int x_val;
    int y_val;
    int frame;
    SDL_Rect clip[18];  
    int down;
    int up;
    int left;
    int right;
    int heart;
    int x_val_1;
};



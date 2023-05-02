#pragma once
#include <vector>
#include "Function.h"
#include "RenderWindow.h"


#define WIDTH_MAIN 70
#define HEIGHT_MAIN 57
#define MAIN_SPEED 20
#define MAIN_HEART 3

class Space : public RenderWindow {
public:
    Space();
    ~Space();
    bool loadTexture(std::string path, SDL_Renderer* screen);
    void eventSpace(SDL_Event event, SDL_Renderer* screen);
    void set_x_val(const int& x) { x_val = x; }
    void set_y_val(const int& x) { y_val = x; }
    int get_x_val() { return x_val; }
    int get_y_val() { return y_val; }
    void set_heart(const int& x) { heart = x; }
    int get_heart() { return heart; }
    bool get_init() { return init; }

    void HandleMove(SDL_Event event, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void ShowBullet(SDL_Renderer* des);
    void Remove();
    void Refresh();
    void set_dame(const int& x) { dame = x; }
    int get_dame() { return dame; }
private:
    
    int x_val;
    int y_val;
    int x_pos;
    int y_pos;
    int heart;
    bool init;
    int dame;
    
};
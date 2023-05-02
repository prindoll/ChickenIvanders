#pragma once
#include "Function.h"
#include "RenderWindow.h"

#define WIDTH_FRAME 150
#define HEIGHT_FRAME_Explore 165
#define NUMBER_OF_FRAME 8

class Explore : public RenderWindow {
public:
    Explore();
    ~Explore();

    void set_clip();
    void Show(SDL_Renderer* screen);

    void set_frame(const int& Frame) { frame = Frame; }
    int get_frame()const { return frame; }
private:
    int frame;
    SDL_Rect clip[8];
};
#pragma once
#include "Function.h"
#include "RenderWindow.h"

class Text : public RenderWindow {
public:
    Text();
    ~Text();

    enum TEXT_COLOR {
        RED = 0,
        WHITE = 1,
        BLACK = 2,
    };

    void SetText(const std::string& x) { text = x; }
    void SetColor(const int& type);
    void showText(TTF_Font* font, SDL_Renderer* screen);
    void Free();
private:
    std::string text;
    SDL_Texture* texture;
    SDL_Color text_color;
};
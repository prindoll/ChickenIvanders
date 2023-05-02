#include "Text.h"

Text::Text() {
    
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
}
Text::~Text() {

}
void Text::SetColor(const int& type) {
    if (type == 0) {
        text_color = { 255,0,0 };
    }
    else if (type == 1) {
        text_color = { 255,255,255 };
    }
    else if (type == 2) {
        text_color = { 0,0,0 };
    }
}
void Text::showText(TTF_Font* font, SDL_Renderer* screen) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), text_color);
    if (textSurface != NULL) {
        texture = SDL_CreateTextureFromSurface(screen, textSurface);
        if (texture != NULL) {
            rect.w = textSurface->w;
            rect.h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    SDL_Rect renderQuad = { rect.x ,rect.y , rect.w ,rect.h };
    SDL_RenderCopy(screen, texture, NULL, &renderQuad);
}
void Text::Free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;

    }
}
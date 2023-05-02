#include "RenderWindow.h"

RenderWindow::RenderWindow() {
    gTexture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}
RenderWindow::~RenderWindow() {
    
}
bool RenderWindow::loadTexture(std::string path, SDL_Renderer* screen) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL) {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        if (newTexture != NULL) {
            rect.w = loadSurface->w;
            rect.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    gTexture = newTexture;
    return gTexture != NULL;
}
void RenderWindow::Render(SDL_Renderer* screen) {
    SDL_Rect renderQuad = { rect.x ,rect.y , rect.w ,rect.h };
    SDL_RenderCopy(screen, gTexture, NULL, &renderQuad);
}
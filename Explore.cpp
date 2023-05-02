#include "Explore.h"

Explore::Explore() {
    frame = 0;
}
Explore::~Explore() {

}
void Explore::set_clip() {
    for (int i = 0; i < 8; i++) {
        clip[i].x = i * 150;
        clip[i].y = 0;
        clip[i].w = 150;
        clip[i].h = 165;
    }
}

void Explore::Show(SDL_Renderer* screen) {
    SDL_Rect renderQuad = { rect.x,rect.y, 150,165 };
    SDL_RenderCopy(screen, gTexture, &clip[frame], &renderQuad);
}
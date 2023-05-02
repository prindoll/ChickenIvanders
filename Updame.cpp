#include"Updame.h"

Updame::Updame() {
	frame = 0;
	is_move = false;
}
Updame::~Updame() {

}
void Updame::set_clip() {
    for (int i = 0; i < 25; i++) {
        clip[i].x = i * WIDTH_DAME;
        clip[i].y = 0;
        clip[i].w = WIDTH_DAME;
        clip[i].h = HEIGHT_DAME;
    }
}
SDL_Rect Updame::GetFrame() {
    SDL_Rect Frame1;
    Frame1.x = rect.x;
    Frame1.y = rect.y;
    Frame1.w = WIDTH_DAME;
    Frame1.h = HEIGHT_DAME;
    return Frame1;
}
void Updame::Show(SDL_Renderer* screen) {
    frame++;
    if (frame >= 25) {
        frame = 0;
    }
    SDL_Rect renderQuad = { rect.x,rect.y,WIDTH_DAME,HEIGHT_DAME };
    SDL_RenderCopy(screen, gTexture, &clip[frame], &renderQuad);
}
void Updame::HandleUpdame() {
    if (rect.y <= SCREEN_HEIGHT) {
        rect.y += 5;
    }
    if (rect.y > SCREEN_HEIGHT) {
        is_move = false;
    }
}
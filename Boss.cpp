#include "Boss.h"
Boss::Boss() {
    
    x_val = 0;
    y_val = 0;
    down = 0;
    up = 0;
    left = 1;
    right = 0;
    frame = 0;
    heart = 300;
}
Boss::~Boss() {

}
SDL_Rect Boss::GetFrame() {
    SDL_Rect Frame1;
    Frame1.x = rect.x;
    Frame1.y = rect.y;
    Frame1.w = WIDTH_BOSS;
    Frame1.h = HEIGHT_BOSS;
    return Frame1;
}
void Boss::set_clips() {
    for (int i = 0; i < 10; i++) {
        clip[i].x = i * WIDTH_BOSS;
        clip[i].y = 0;
        clip[i].w = WIDTH_BOSS;
        clip[i].h = HEIGHT_BOSS;
    }
}
void Boss::Show(SDL_Renderer* screen) {
    frame++;
    if (frame >= 10) {
        frame = 0;
    }
    SDL_Rect renderQuad = { rect.x,rect.y,WIDTH_BOSS,HEIGHT_BOSS };
    SDL_RenderCopy(screen, gTexture, &clip[frame], &renderQuad);
}


void Boss::Move() {
    rect.y += y_val;
    if (left) {
        rect.x -= x_val;
    }
    if (right) {
        rect.x += x_val;
    }
    if (up) {
        rect.y -= 2 * y_val;
    }

    if (rect.y > SCREEN_HEIGHT - HEIGHT_BOSS) {
        up = 1;
        down = 0;
    }
    else if (rect.y < 0) {
        down = 1;
        up = 0;
    }
    if (rect.x <= 0) {
        right = 1;
        left = 0;
    }
    else if (rect.x >= SCREEN_WIDTH - WIDTH_BOSS) {
        left = 1;
        right = 0;
    }
}
void Boss::show_heart_boss(SDL_Renderer* screen, int x, int y, int w, int h) {
    SDL_Rect fill_rect = { x,y,w,h };
    SDL_SetRenderDrawColor(screen, 255, 0, 0, 255);
    SDL_RenderFillRect(screen, &fill_rect);
}
void Boss::Delete() {
    this->setRect(-100, -100);
}

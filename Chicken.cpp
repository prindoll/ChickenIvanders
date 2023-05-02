#include"Chicken.h"

Chicken::Chicken() {
    rect.x = SCREEN_WIDTH;
    rect.y = SCREEN_HEIGHT / 2;
    x_val = 0;
    y_val = 0;
    down = 0;
    up = 0;
    left = 0;
    right = 1;
    frame = 0;
    x_val_1 = 0;
}
Chicken::~Chicken() {

}
void Chicken::set_clip() {
    for (int i = 0; i < 18; i++) {
        clip[i].x = i * WIDTH_CHICKEN;
        clip[i].y = 0;
        clip[i].w = WIDTH_CHICKEN;
        clip[i].h = HEIGHT_CHICKEN;
    }
}
void Chicken::Show(SDL_Renderer* screen) {
    frame++;
    if (frame >= 18) {
        frame = 0;
    }
    SDL_Rect renderQuad = { rect.x,rect.y,WIDTH_CHICKEN,HEIGHT_CHICKEN };
    SDL_RenderCopy(screen, gTexture, &clip[frame], &renderQuad);
}

void Chicken::Move() {
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

    if (rect.y > SCREEN_HEIGHT) {
        up = 1;
        down = 0;
    }
    else if (rect.y + HEIGHT_CHICKEN < 0) {
        down = 1;
        up = 0;
    }
    if (rect.x <= -WIDTH_CHICKEN * 3) {
        right = 1;
        left = 0;
    }
    else if (rect.x >= SCREEN_WIDTH + 3 * WIDTH_CHICKEN) {
        left = 1;
        right = 0;
    }
}

void Chicken::Move1() {
    if (rect.y < 300) {
        rect.y += y_val;
    }
}

SDL_Rect Chicken::GetFrame() {
    SDL_Rect Frame1;
    Frame1.x = rect.x;
    Frame1.y = rect.y;
    Frame1.w = WIDTH_CHICKEN;
    Frame1.h = HEIGHT_CHICKEN;
    return Frame1;
}
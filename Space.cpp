#include"Space.h"

Space::Space() {
    rect.x = 550;
    rect.y = 650;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    init = true;
    heart = 3;
    dame = 1;
}

Space::~Space() {
   
}

bool Space::loadTexture(std::string path, SDL_Renderer* screen) {
    bool ret = RenderWindow::loadTexture(path.c_str(), screen);
    return ret;
}
void Space::eventSpace(SDL_Event event, SDL_Renderer* screen) {
    if (event.type == SDL_KEYDOWN ) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            y_val = -MAIN_SPEED;
            break;
        case SDLK_s:
            y_val = MAIN_SPEED;
            break;
        case SDLK_d:
            x_val = +MAIN_SPEED;
            break;
        case SDLK_a:
            x_val = -MAIN_SPEED;
            break;
        }
    }
    
}
void Space::Show(SDL_Renderer* des) {
   
    
    rect.y += y_val;
    rect.x += x_val;
    if (rect.x < 0 || rect.x + WIDTH_MAIN > SCREEN_WIDTH) {
        rect.x -= x_val;
    }
    if (rect.y < 0 || rect.y + HEIGHT_MAIN > SCREEN_HEIGHT) {
        rect.y -= y_val;
    }
    x_val = 0;
    y_val = 0;
    SDL_Rect renderQuad = { rect.x ,rect.y , rect.w ,rect.h };
    SDL_RenderCopy(des, gTexture, NULL, &renderQuad);
}

void Space::ShowBullet(SDL_Renderer* des) {
    SDL_Rect renderQuad = { rect.x ,rect.y , rect.w ,rect.h };
    SDL_RenderCopy(des, gTexture, NULL, &renderQuad);
}
void Space::Remove() {
    init = false;
    this->setRect(-150, -150);
}
void Space::Refresh() {
    rect.x = 550;
    rect.y = 650;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    init = true;
}


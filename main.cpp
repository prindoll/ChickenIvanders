#include"Function.h"
#include"RenderWindow.h"
#include"Space.h"
#include"Bullet.h"
#include"Chicken.h"
#include"Time.h"
#include<vector>
#include<cstdlib>
#include<iostream>
#include<string>
#include"Boss.h"
#include"Explore.h"
#include"Text.h"
#include"Updame.h"
int f = 0;
int score_int = 0;
RenderWindow gBackground;
RenderWindow gMenu;
RenderWindow gScore;
RenderWindow gIntroduce;
RenderWindow pause1;
RenderWindow pause2;
Space space;
Explore exps;
std::vector<Bullet*> p_bullet_list;
std::vector<Chicken*> chicken_1;
std::vector<Chicken*> chicken_2;
std::vector<Chicken*> chicken_3;
std::vector<Chicken*> chicken_e;
std::vector<Bullet*> bullet_chicken;
Bullet* bullet_boss;
Boss* boss;
Time time_fps;
TTF_Font* menu_font;
TTF_Font* score_font; 
TTF_Font* end_font;
Text continueGame;
Text menu[3];
Text back;
Text wave;
Text score[3];
Text endGame[2];
Updame updame;
std::string gun[4] = {"img/gun1.png",
                      "img/gun2.png",  
                      "img/gun3.png", 
                      "img/gun4.png"};


bool checkInit() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        success = false;
    }
    else {
        gWindow = SDL_CreateWindow("Chicken Ivanders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            success = false;
        }
        else {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gScreen == NULL) {
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    success = false;
                }
                
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    success = false;
                }
                // Init Music
                gShoot = Mix_LoadWAV("sound/shoot.wav");
                gClick = Mix_LoadWAV("sound/click.wav");
                gChicken[0] = Mix_LoadWAV("sound/hit1.wav");
                gChicken[1] = Mix_LoadWAV("sound/hit2.wav");
                gExp = Mix_LoadWAV("sound/exp.wav");
                EndGame[0] = Mix_LoadWAV("sound/win.wav");
                EndGame[1] = Mix_LoadWAV("sound/lose.wav");

                if (TTF_Init() < 0) {
                    success = false;
                }
                // Init TTF
                menu_font = TTF_OpenFont("font/play.ttf", 50);
                score_font = TTF_OpenFont("font/score.ttf", 30);
                end_font = TTF_OpenFont("font/play.ttf", 70);
            }
        }
    }
    return success;
}
bool loadBackground() {
    bool k[9];
    k[0] = gBackground.loadTexture("img/background.png", gScreen);
    k[1] = space.loadTexture("img/space.png", gScreen);
    k[2] = exps.loadTexture("img/exp.png", gScreen);
    k[3] = gMenu.loadTexture("img/menu2.png", gScreen);
    k[4] = gScore.loadTexture("img/score.png", gScreen);
    k[5] = updame.loadTexture("img/up.png", gScreen);
    k[6] = pause1.loadTexture("img/pause1.png", gScreen);
    k[7] = pause2.loadTexture("img/pause2.png", gScreen);
    k[8] = gIntroduce.loadTexture("img/menu.png", gScreen);
    for (int i = 0; i < 9; i++) {
        if (k[i] == false) {
            return 0;
        }
    }
    return 1;
}
bool check_collision(const SDL_Rect& object1, const SDL_Rect& object2) {
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b) {
        return false;
    }
    return true;
}
bool check_mouse(const int& x, const int& y, const SDL_Rect& rect) {
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}

void loadText() {
   
    menu[0].SetColor(Text::WHITE);
    menu[0].SetText("Play");
    menu[0].setRect(300, 450);
    menu[1].SetColor(Text::WHITE);
    menu[1].SetText("Instruct");
    menu[1].setRect(300, 530);
    menu[2].SetColor(Text::WHITE);
    menu[2].SetText("Exit");
    menu[2].setRect(300, 610);
    score[0].SetColor(Text::WHITE);
    score[0].setRect(80, 0);
    score[1].SetColor(Text::WHITE);
    score[1].setRect(220, 0); 
    score[2].SetColor(Text::WHITE);
    score[2].setRect(310, 0);
    back.SetColor(Text::WHITE);
    back.setRect(0, 0);
    back.SetText("Back");
    gScore.setRect(0, 10);
    pause1.setRect(1100, 0);
    pause2.setRect(1100, 0);
    wave.setRect(450, 300);
    wave.SetColor(Text::WHITE);
    wave.SetText("Wave one");
    endGame[0].setRect(450, 300);
    endGame[0].SetColor(Text::WHITE);
    endGame[0].SetText("Game Over");
    endGame[1].setRect(450, 300);
    endGame[1].SetColor(Text::WHITE);
    endGame[1].SetText("You Win");
    continueGame.setRect(350, 300);
    continueGame.SetColor(Text::WHITE);
    continueGame.SetText("Press U to continue");
}
void CreateChiken() {
    int t = 0;
    int y_row = 0;
    for (int c = 0; c < 12; c++) {
        Chicken* p_chicken = new Chicken();
        if (p_chicken) {
            p_chicken->loadTexture("img/chicken_red.png", gScreen);
            p_chicken->set_clip();
            if (t % 12 == 0) {
                y_row -= 100;
                t = 0;
            }
            p_chicken->setRect(10 + t * 90, y_row);
            p_chicken->set_y_val(2);
            p_chicken->set_x_val(2);
            p_chicken->set_heart(3);
            chicken_1.push_back(p_chicken);
            t++;
        }
    }
    t = 0;
    y_row = 0;
    for (int c = 0; c < 24; c++) {
        Chicken* p_chicken = new Chicken();
        if (p_chicken) {
            p_chicken->loadTexture("img/chicken_red.png", gScreen);
            p_chicken->set_clip();
            if (t % 12 == 0) {
                y_row -= 100;
                t = 0;
            }
            p_chicken->setRect(10 + t * 90, y_row);
            p_chicken->set_y_val(4);
            p_chicken->set_x_val(4);
            p_chicken->set_heart(3);
            chicken_2.push_back(p_chicken);
            t++;
        }
    }
    t = 0;
    y_row = 0;
    for (int c = 0; c < 36; c++) {
        Chicken* p_chicken = new Chicken();
        if (p_chicken) {
            p_chicken->loadTexture("img/chicken_red.png", gScreen);
            p_chicken->set_clip();
            if (t % 12 == 0) {
                y_row -= 100;
                t = 0;
            }
            p_chicken->setRect(10 + t * 90, y_row);
            p_chicken->set_y_val(4);
            p_chicken->set_x_val(4);
            p_chicken->set_heart(3);
            chicken_3.push_back(p_chicken);
            t++;
        }
    }
    srand(NULL);
    for (int i = 0; i < 10; i++) {
        int random = rand() % (chicken_1.size() - 2);
        Bullet* chickenBullet = new Bullet();
        chickenBullet->loadTexture("img/egg.png", gScreen);
        chickenBullet->set_y_val(5);
        chickenBullet->setRect(chicken_1[random]->getRectX(), chicken_1[random]->getRectY());
        bullet_chicken.push_back(chickenBullet);
    }
    updame.set_clip();
    exps.set_clip();
}


void CreateBoss() {
    boss = new Boss();
    boss->loadTexture("img/boss.png", gScreen);
    boss->set_clips();
    boss->setRect(0, 0);
    boss->set_y_val(3);
    boss->set_x_val(9);
    
    bullet_boss = new Bullet();
    bullet_boss->loadTexture("img/egg_boss.png", gScreen);
    bullet_boss->set_y_val(20);
    bullet_boss->setRect(boss->getRectX() + 100, boss->getRectY() + 50);
}
void RemoveBullet(const int& x) {
    int size = p_bullet_list.size();
    if (size > 1 && x < size && x > 0) {
        Bullet* p_bul = p_bullet_list.at(x);
        p_bullet_list.erase(p_bullet_list.begin() + x);
        if (p_bul != NULL) {
            p_bul->Free();
            p_bul = NULL;
        }
    }
}
void EraseBullet() {
    for (int i = 0; i < 10; i++) {
        bullet_chicken[i]->set_is_bullet(false);
    }
}
void InitBullet() {
    for (int i = 0; i < 10; i++) {
        bullet_chicken[i]->set_is_bullet(true);
    }
}
void close() {
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gScreen);
    gWindow = NULL;
    gScreen = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}






int main(int argc, char* argv[]) {
    srand(NULL);
    int slip = -(3840 - SCREEN_HEIGHT);
    int co = 0;
    int pp = 0;
    if (checkInit() == false) return -2;
    if (loadBackground() == false) return -1;
    CreateChiken();
    CreateBoss();
    loadText();
    bool pause = 0;
    int quit = 0;
    while (quit <= 2) {
        while (quit == 0) {
            while (SDL_PollEvent(&gEvent) != 0) {
                int xm = gEvent.motion.x;
                int ym = gEvent.motion.y;
                if (gEvent.type == SDL_QUIT) {
                    quit = 4;
                }
                if (gEvent.type == SDL_MOUSEMOTION) {
                    
                    for (int i = 0; i < 3; i++) {
                        if (check_mouse(xm, ym, menu[i].getRect())) {
                            menu[i].SetColor(Text::RED);
                        }
                        else {
                            menu[i].SetColor(Text::WHITE);
                        }
                    }
                }
                if (gEvent.type = SDL_MOUSEBUTTONDOWN) {
                    for (int i = 0; i < 3; i++) {
                        if (check_mouse(xm, ym, menu[i].getRect()) && gEvent.button.button == SDL_BUTTON_LEFT) {
                            Mix_PlayChannel(-1, gClick, 0);
                            quit = i + 1;
                        }
                    }
                }
            }
            SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(gScreen);
            gMenu.Render(gScreen);
            for (int m = 0; m < 3; m++) {
                menu[m].Free();
                menu[m].showText(menu_font ,gScreen);

            }
            SDL_RenderPresent(gScreen);
        }
        while (quit == 1) {
            if (pp <= 150) {
                pp++;
            }
            time_fps.start();
            while (SDL_PollEvent(&gEvent) != 0) {
                int xm = gEvent.motion.x;
                int ym = gEvent.motion.y;
                int dame_s = 0;
                if (gEvent.type == SDL_QUIT) {
                    quit = 4;
                }
                space.eventSpace(gEvent, gScreen);
                if (gEvent.type == SDL_MOUSEBUTTONDOWN) {

                    if (gEvent.button.button == SDL_BUTTON_LEFT) {
                        if (check_mouse(xm, ym, pause1.getRect())) {
                            pause = 1;
                        }


                        else {
                            if (space.get_dame() - 1 <= 3) dame_s = space.get_dame() - 1;
                            else {
                                dame_s = 3;
                            }
                            Mix_PlayChannel(-1, gShoot, 0);
                            Bullet* p_bullet = new Bullet();
                            p_bullet->loadTexture(gun[dame_s], gScreen);
                            p_bullet->setRect(space.getRectX() + 25 - dame_s*5, space.getRectY() - 15);
                            p_bullet->set_y_val(20);
                            p_bullet->set_is_bullet(true);
                            p_bullet_list.push_back(p_bullet);
                        }
                        
                    }
                }
                if (gEvent.type == SDL_KEYUP) {
                    if (gEvent.key.keysym.sym == SDLK_u) {
                        space.Refresh();
                        exps.set_frame(0);
                    }
                }
            }
            SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(gScreen);
            slip += 1;
            if (slip < 0) {
                gBackground.Render(gScreen);
                gBackground.setRect(0, slip);
            }
            else {
                gBackground.Render(gScreen);
                gBackground.setRect(0, 0);
            }
            space.Show(gScreen);

            int size = p_bullet_list.size();
            if (size != 0) {
                for (int b = 0; b < p_bullet_list.size(); b++) {
                    Bullet* p_bul = p_bullet_list[b];
                    if (p_bul != NULL) {
                        if (p_bul->get_is_bullet()) {
                            p_bul->HandleBullet();
                            p_bul->Render(gScreen);
                        }
                        else {

                            p_bul->Free();
                            p_bul = NULL;
                            if (b < p_bullet_list.size())
                                RemoveBullet(b);

                        }
                    }
                }
            }

            if (!chicken_1.empty() && pp >= 140) {
                for (int ck = 0; ck < chicken_1.size(); ck++) {
                    Chicken* p_chicken = chicken_1.at(ck);
                    if (p_chicken)
                    {
                        p_chicken->Move();
                        p_chicken->Show(gScreen);
                    }
                }
                for (int bl = 0; bl < 10; bl++) {
                    if (bl <= (int)(chicken_1.size() / 6) + 1) {
                        if (bullet_chicken[bl]->get_is_bullet()) {
                            bullet_chicken[bl]->ChickenBullet();
                            bullet_chicken[bl]->Render(gScreen);
                        }
                        else {
                            int random = rand() % 36;
                            if (random >= 0 && random < chicken_1.size()) {
                                bullet_chicken[bl]->setRect(chicken_1[random]->getRectX(), chicken_1[random]->getRectY());
                                bullet_chicken[bl]->set_is_bullet(true);
                            }
                        }
                    }
                    
                }

            }


            // check

            if (!chicken_1.empty() && pp >= 140) {
                for (int bl = 0; bl < chicken_1.size(); bl++) {
                    Chicken* chicken = chicken_1.at(bl);
                    if (check_collision(space.getRect(), chicken->GetFrame()) && space.get_init())
                    {
                        space.set_heart(space.get_heart() - 1);
                        exps.setRect(space.getRectX(), space.getRectY());
                        space.Remove();

                    }
                    int size = p_bullet_list.size();
                    if (size != 0) {
                        for (int i = 0; i < p_bullet_list.size(); i++) {
                            Bullet* p_bul = p_bullet_list.at(i);
                            if (check_collision(p_bul->getRect(), chicken->GetFrame())) {
                                Mix_PlayChannel(-1, gChicken[0], 0);
                                chicken->set_heart(chicken->get_heart() - space.get_dame());
                                p_bul->Free();
                                p_bul = NULL;

                                if (chicken->get_heart() <= 0) {
                                    Mix_PlayChannel(-1, gChicken[1], 0);
                                    chicken_1.erase(chicken_1.begin() + bl);
                                    score_int++;
                                }
                                if (i < p_bullet_list.size())
                                    RemoveBullet(i);
                            }
                        }
                    }

                }

                for (int bt = 0; bt < 10; bt++) {
                    if (bt <= (int)(chicken_1.size() / 6) + 1) {
                        if (check_collision(space.getRect(), bullet_chicken[bt]->getRect()) && space.get_init()) {
                            bullet_chicken[bt]->set_is_bullet(false);
                            space.set_heart(space.get_heart() - 1);
                            exps.setRect(space.getRectX(), space.getRectY());
                            space.Remove();
                        }
                    }
                   
                }
            }

            // set new wave
            if (chicken_1.empty() && !chicken_2.empty()) {
                chicken_1 = chicken_2;
                chicken_2 = chicken_e;
                pp = 0;
                wave.SetText("Wave Two");

            }
            if (chicken_1.empty() && !chicken_3.empty()) {
                chicken_1 = chicken_3;
                chicken_3 = chicken_e;
                pp = 0;
                wave.SetText("Wave Three");
            }
            if (chicken_1.empty() && chicken_3.empty() && f == 0) {
                wave.SetText("Boss");
                pp = 0;
                f = 1;
            }
            if (pp == 0) {
                EraseBullet();
            }
            if (pp <= 140) {
                wave.Free();
                wave.showText(menu_font, gScreen);
            }
            
            // boss
            if (chicken_1.empty() && boss != NULL && pp >= 140) {
                if (boss->get_heart() > 0) {
                    boss->Move();
                    boss->Show(gScreen);
                    boss->show_heart_boss(gScreen, boss->getRectX() - 20, boss->getRectY() - 20, boss->get_heart(), 6);
                    if (bullet_boss->get_is_bullet()) {
                        bullet_boss->ChickenBullet();
                        bullet_boss->Render(gScreen);
                    }
                    else
                    {
                        bullet_boss->setRect(boss->getRectX() + 100, boss->getRectY() + 50);
                        bullet_boss->set_is_bullet(true);
                    }
                }
               
                int size = p_bullet_list.size();
                if (size != 0) {
                    for (int i = 0; i < p_bullet_list.size(); i++) {
                        Bullet* p_bul = p_bullet_list.at(i);
                        if (check_collision(p_bul->getRect(), boss->GetFrame())) {
                            boss->set_heart(boss->get_heart() - space.get_dame());
                            Mix_PlayChannel(-1, gChicken[0], 0);
                            p_bul->Free();
                            p_bul = NULL;
                            RemoveBullet(i);
                        }
                    }
                    if (check_collision(space.getRect(), boss->GetFrame()) && boss != NULL) {
                        space.set_heart(space.get_heart() - 1);
                        exps.setRect(space.getRectX(), space.getRectY());
                        space.Remove();
                    }
                    if (check_collision(space.getRect(), bullet_boss->getRect())) {
                        space.set_heart(space.get_heart() - 1);
                        exps.setRect(space.getRectX(), space.getRectY());
                        space.Remove();
                        bullet_boss->set_is_bullet(false);
                    }

                }
                if (boss->get_heart() <= 0) {
                    boss->Delete();
                    boss = NULL;
                }
            }
            if (space.get_heart() <= 0){
                endGame[0].Free();
                endGame[0].showText(end_font, gScreen);
                if (co == 0) {
                    Mix_PlayChannel(-1, EndGame[1], 0);
                    co = 1;
                }
            }
            if (boss == NULL) {
                endGame[1].Free();
                endGame[1].showText(end_font, gScreen);
                if (co == 0) {
                    Mix_PlayChannel(-1, EndGame[0], 0);
                    co = 1;
                }
            }

            if (space.get_init() == false) {
                if (exps.get_frame() < 4) {

                    exps.Show(gScreen);
                    exps.set_frame(exps.get_frame() + 1);

                }
                if (exps.get_frame() == 1) {
                    Mix_PlayChannel(-1, gExp, 0);
                }
                if (space.get_heart() > 0) {
                    continueGame.Free();
                    continueGame.showText(end_font, gScreen);
                }

            }
            if (space.get_init() == true && updame.get_is_move() == false) {
                int k = rand() % 10000;
                if (k <= 9) {
                    updame.set_is_move(true);
                    updame.setRect(SCREEN_WIDTH / 10 * k, 0);
                    
                }
            }
            if (updame.get_is_move()) {
                updame.HandleUpdame();
                updame.Show(gScreen);
                if (check_collision(space.getRect(), updame.GetFrame()) && space.get_init()) {
                    space.set_dame(space.get_dame() + 1);
                    Mix_PlayChannel(-1, gClick, 0);
                    updame.set_is_move(false);
                }
            }
            if (pause == 0) {
                pause1.Render(gScreen);
            }
            if (pause == 1) {
                pause2.Render(gScreen);
            }
            
            score[0].SetText(std::to_string(score_int));
            score[1].SetText(std::to_string(space.get_heart()));
            score[2].SetText(std::to_string(space.get_dame()));
            
            gScore.Render(gScreen);
            for (int s = 0; s < 3; s++) {
                score[s].Free();
                score[s].showText( score_font, gScreen);
            }

            
            SDL_RenderPresent(gScreen);
            while (pause == 1) {
                while (SDL_PollEvent(&gEvent) != 0) {
                    int xm = gEvent.motion.x;
                    int ym = gEvent.motion.y;
                    if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                        if (gEvent.button.button == SDL_BUTTON_LEFT && check_mouse(xm, ym, pause2.getRect()) ) {
                            pause = 0;
                        }
                    }
                }
            }
            int real_time = time_fps.get_time();
            if (real_time < 1000 / FPS) {
                SDL_Delay(1000 / FPS - real_time);
            }
        }
        while (quit == 2) {
            while (SDL_PollEvent(&gEvent) != 0) {
                if (gEvent.type == SDL_QUIT) {
                    quit = 4;
                }
                int xm = gEvent.motion.x;
                int ym = gEvent.motion.y;
                if (gEvent.type == SDL_MOUSEMOTION) {
                    if (check_mouse(xm, ym, back.getRect())) {
                        back.SetColor(Text::RED);
                    }
                    else back.SetColor(Text::WHITE);
                }
                if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                    if (gEvent.button.button == SDL_BUTTON_LEFT) {
                        quit = 0;
                    }
                }
            }
            SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(gScreen);
            gIntroduce.Render(gScreen);
            back.Free();
            back.showText(menu_font, gScreen);
            SDL_RenderPresent(gScreen);
        }
    }
    close();

    return 0;
}
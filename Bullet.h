#pragma once
#include "Function.h"
#include "RenderWindow.h"

class Bullet : public RenderWindow {
public:
    Bullet();
    ~Bullet();

    void set_x_val(const int& xVal) { x_val = xVal; }
    void set_y_val(const int& yVal) { y_val = yVal; }
    int get_x_val()const { return x_val; }
    int get_y_val()const { return y_val; }
    void set_is_bullet(const bool& isMove) { is_bullet = isMove; }
    bool get_is_bullet()const { return is_bullet; }
    void HandleBullet();
    void Free();
    void ChickenBullet();
private:
    int x_val;
    int y_val;
    bool is_bullet;
};
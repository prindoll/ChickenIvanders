#include"Bullet.h"


Bullet::Bullet() {
	x_val = 0;
	y_val = 0;
	is_bullet = true;
}
Bullet::~Bullet() {

}

void Bullet::HandleBullet() {
	rect.y -= y_val;
	if (rect.y < 0) {
		is_bullet = false;
	}
}
void Bullet::Free() {
	this->setRect(-150, -150);
}
void Bullet::ChickenBullet() {
	rect.y += y_val;
	if (rect.y > SCREEN_HEIGHT) {
		is_bullet = false;
	}
}
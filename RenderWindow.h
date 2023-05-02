#pragma once
#include"Function.h"


class RenderWindow {
public:

	RenderWindow();
	~RenderWindow();
	void setRect(const int& x, const int& y) { rect.x = x; rect.y = y; }
	virtual bool loadTexture(std::string path, SDL_Renderer* screen);
	SDL_Rect getRect() const { return rect; }
	SDL_Texture* getTexture() const { return gTexture; }
	void Render(SDL_Renderer* des);
	int getRectX() const { return rect.x; }
	int getRectY() const { return rect.y; }


protected:
	SDL_Rect rect;
	SDL_Texture* gTexture;
};
#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "EventHandler.hpp"
#include <vector>

class A2D_LIB Body {
public:
	Body(Image& im, BodyRectangle& rect);
	void draw();
	void draw(int w, int h);
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	void update(float gravity = 0);
	Image& image;
	BodyRectangle& rectangle;
	bool suffer_gravity = true;
	bool can_collide = true;
	float accel_x = 0, accel_y = 0;
	float vel_x = 0, vel_y = 0;
};
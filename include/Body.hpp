#pragma once

#include "Image.hpp"
#include "BodyRectangle.hpp"

class Body {
public:
	Body(Image& im, BodyRectangle& rect);
	void draw();
	void draw(int w, int h);
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	Image image;
	BodyRectangle rectangle;
};
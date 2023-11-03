#pragma once

#include "Image.hpp"
#include "BodyRectangle.hpp"

class Body {
public:
	Body(Image& im, BodyRectangle& rect) : image(im), rectangle(rect) {}
	void draw() {
		image.draw(rectangle.x, rectangle.y);
	}
	void draw(int w, int h) {
		image.draw(rectangle.x, rectangle.y, w, h);
	}
	void setX(int x) { rectangle.x = x; }
	int getX() { return rectangle.x; }
	void setY(int y) {rectangle.x = y;}
	int getY() { return rectangle.y; }
	Image image;
	BodyRectangle rectangle;
};
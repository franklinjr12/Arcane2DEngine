
#include "Body.hpp"

Body::Body() {
	image = nullptr;
	rectangle = nullptr;

}

Body::Body(Image* im, BodyRectangle* rect) {
	image = im;
	rectangle = rect;
}

Body::~Body() {
	if (image) delete image;
	if (rectangle) delete rectangle;
}

void Body::draw() {
	image->draw(rectangle->pos.pos, rectangle->w, rectangle->h);
}

void Body::draw(int w, int h) {
	image->draw(rectangle->pos.pos, w, h);
}

void Body::setX(int x) { rectangle->pos.x = x; }

int Body::getX() { return rectangle->pos.x; }

void Body::setY(int y) { rectangle->pos.y = y; }

int Body::getY() { return rectangle->pos.y; }

void Body::update() {}


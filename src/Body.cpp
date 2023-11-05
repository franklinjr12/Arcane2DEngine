
#include "Body.hpp"

Body::Body(Image& im, BodyRectangle& rect) : image(im), rectangle(rect) {}
void Body::draw() {
	image.draw(rectangle.x, rectangle.y, rectangle.w, rectangle.h);
}
void Body::draw(int w, int h) {
	image.draw(rectangle.x, rectangle.y, w, h);
}
void Body::setX(int x) { rectangle.x = x; }
int Body::getX() { return rectangle.x; }
void Body::setY(int y) { rectangle.y = y; }
int Body::getY() { return rectangle.y; }
void Body::update(float gravity) {
	vel_x += accel_x;
	rectangle.x += vel_x;
	if (suffer_gravity) {
		vel_y += gravity;
	}
	vel_y += accel_y;
	rectangle.y += vel_y;
}
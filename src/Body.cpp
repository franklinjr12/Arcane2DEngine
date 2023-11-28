
#include "Body.hpp"
#include "ArcaneUtils.hpp"

Body::Body() {
	image = nullptr;
	rectangle = nullptr;
	pos = { 0,0 };
}

Body::Body(Image* im, BodyRectangle* rect) {
	image = im;
	rectangle = rect;
	pos = { rect->pos.x, rect->pos.y };
}

Body::~Body() {
	if (image) delete image;
	if (rectangle) delete rectangle;
}

void Body::draw() {
	//image->draw(rectangle->pos.pos, rectangle->w, rectangle->h);
	Vecf p;
	p[0] = pos.x - image->width / 2;
	p[1] = pos.y + image->height / 2;
	image->draw(p, rectangle->w, rectangle->h);
	if (draw_rect_overlay) {
		Image& blue_overlay = GetBlueOverlayImage();
		RGBA_t color = { 1,1,1,OVERLAY_ALPHA };
		blue_overlay.draw(rectangle->pos.pos, color, rectangle->w, rectangle->h);
	}
}

void Body::draw(int w, int h) {
	//image->draw(rectangle->pos.pos, w, h);
	image->draw(rectangle->pos.pos, w, h);
	Vecf p;
	p[0] = pos.x - image->width / 2;
	p[1] = pos.y + image->height / 2;
	image->draw(p, w, h);
	if (draw_rect_overlay) {
		Image& blue_overlay = GetBlueOverlayImage();
		RGBA_t color = { 1,1,1,OVERLAY_ALPHA };
		blue_overlay.draw(rectangle->pos.pos, color, rectangle->w, rectangle->h);
	}
}

void Body::setX(int x) { rectangle->pos.x = x; }

int Body::getX() { return rectangle->pos.x; }

void Body::setY(int y) { rectangle->pos.y = y; }

int Body::getY() { return rectangle->pos.y; }

void Body::update(float gravity) {}


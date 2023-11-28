
#include "Body.hpp"
#include "ArcaneUtils.hpp"

Body::Body() {
	image = nullptr;
	rectangle = nullptr;
	pos = { 0,0 };
}

Body::Body(Image* im, BodyRectangle* rect) {
	image = im;
	// center the image so that body x and y are on center
	rect->pos.x -= image->width / 2;
	rect->pos.y += image->height / 2;
	pos = { rect->pos.x, rect->pos.y };
	rectangle = rect;
}

Body::~Body() {
	if (image) delete image;
	if (rectangle) delete rectangle;
}

void Body::draw() {
	image->draw(pos.pos, rectangle->w, rectangle->h);
	if (draw_rect_overlay) {
		Image& blue_overlay = GetBlueOverlayImage();
		RGBA_t color = { 1,1,1,OVERLAY_ALPHA };
		blue_overlay.draw(rectangle->pos.pos, color, rectangle->w, rectangle->h);
	}
}

void Body::draw(int w, int h) {
	image->draw(pos.pos, w, h);
	if (draw_rect_overlay) {
		Image& blue_overlay = GetBlueOverlayImage();
		RGBA_t color = { 1,1,1,OVERLAY_ALPHA };
		blue_overlay.draw(rectangle->pos.pos, color, rectangle->w, rectangle->h);
	}
}

void Body::setX(int x) {
	pos.x = x;
	rectangle->pos.x = x;
}

int Body::getX() { return pos.x + image->width/2; }

void Body::setY(int y) {
	pos.y = y;
	rectangle->pos.y = y;
}

int Body::getY() { return pos.y + image->height / 2; }

void Body::update(float gravity) {}


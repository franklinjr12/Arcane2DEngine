#include "BodyRectangle.hpp"

BodyRectangle::BodyRectangle(Vecf pos, int width, int height) {
	this->pos.x = pos[0];
	this->pos.y = pos[1];
	w = width;
	h = height;
}

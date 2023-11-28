#pragma once

#include "Surface.hpp"

Surface::Surface(Body& body) : body(body) {}
void Surface::draw() {
	body.draw(body.rectangle->w, body.rectangle->h);
}

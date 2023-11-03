#pragma once

#include "Body.hpp"

class Surface {
public:
	Surface(Body& body) : body(body) {}
	void draw() {
		body.draw(body.rectangle.w, body.rectangle.h);
	}
	Body body;
};
#pragma once

#include "Body.hpp"

class StaticBody : public Body {
public:

	StaticBody(){}
	StaticBody(Image* im, BodyRectangle* rect) : Body(im, rect) {

	}
};
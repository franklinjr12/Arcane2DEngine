#pragma once

#include "Body.hpp"

class StaticBody : public Body {
public:

	StaticBody(){}
	StaticBody(Image* im, BodyRectangle* rect) : Body(im, rect) {
	}
	StaticBody(std::vector<char>& serialized_data) : Body(serialized_data) {
	}
	std::vector<char> serialize() {
		return Body::serialize();
	}
};
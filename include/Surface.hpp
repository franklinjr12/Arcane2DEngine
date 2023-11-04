#pragma once

#include "Body.hpp"

class Surface {
public:
	Surface(Body& body);
	void draw();
	Body body;
};
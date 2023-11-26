#pragma once

#include "Arcane2DLib.hpp"
#include "Types.hpp"

class A2D_API BodyRectangle {
public:

	BodyRectangle(Vecf pos, int width, int height);

	Point pos;
	int w, h;
};
#pragma once

#include "Arcane2DLib.hpp"

class A2D_LIB BodyRectangle {
public:
	BodyRectangle(float x, float y, int width, int height);
	float x, y;
	int w, h;
};
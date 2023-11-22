#pragma once
#include "BodyRectangle.hpp"

class A2D_LIB Collisions {
public:
	static bool isRectColliding(BodyRectangle& a, BodyRectangle& b);
	static bool isPointRectColliding(BodyRectangle& a, int x, int y);
};
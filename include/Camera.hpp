#pragma once

#include "Arcane2DLib.hpp"
#include "BodyRectangle.hpp"

class A2D_API Camera {
public:
	Camera(int x, int y, int w, int h);
	BodyRectangle rect;
};
#pragma once

#include "BodyRectangle.hpp"

class Camera {
public:
	Camera(int x, int y, int w, int h);
	BodyRectangle rect;
};
#pragma once
#include "Arcane2DLib.hpp"
#include "BodyRectangle.hpp"

bool A2D_LIB isRectColliding(BodyRectangle& a, BodyRectangle& b);
bool A2D_LIB isPointRectColliding(BodyRectangle& a, int x, int y);

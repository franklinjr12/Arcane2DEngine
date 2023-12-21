#pragma once

#include "Arcane2DLib.hpp"
#include "ArcaneTypes.hpp"

#include <vector>

class A2D_API BodyRectangle {
public:

	BodyRectangle(Vecf pos, int width, int height);
	BodyRectangle(std::vector<char> serialized_data);
	std::vector<char> serialize();

	Point pos;
	int w, h;
};
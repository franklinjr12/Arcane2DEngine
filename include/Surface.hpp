#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"

class A2D_API Surface {
public:
	Surface(Body& body);
	void draw();
	Body& body;
};
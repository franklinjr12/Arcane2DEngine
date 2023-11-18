#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"

class A2D_LIB Particle {
public:
	Particle(Body& body) : body(body) {}
	bool should_erase = false;
	Body& body;
};
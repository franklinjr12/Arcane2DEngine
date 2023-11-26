#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"

class A2D_API Particle {
public:
	Particle(Body& body) : body(body) {}
	~Particle() {}
	bool should_erase = false;
	Body& body;
};
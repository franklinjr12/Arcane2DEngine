#pragma once

#include "Body.hpp"

class Particle {
public:
	Particle(Body& body) : body(body) {}
	bool should_erase = false;
	Body& body;
};
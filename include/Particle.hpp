#pragma once

#include "Body.hpp"

class Particle {
public:
	Particle(Body& body) : body(body) {}
	Body& body;
};
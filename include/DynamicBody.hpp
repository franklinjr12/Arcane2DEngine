#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"
#include "Types.hpp"

class A2D_API DynamicBody : public Body {
public:

	
	DynamicBody();
	DynamicBody(Image* im, BodyRectangle* rect);
	virtual void update(float gravity=0) override;
	virtual void _update() {}

	Vecf accel;
	Vecf vel;
	bool suffer_gravity = false;
};
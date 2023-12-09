#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"
#include "ArcaneTypes.hpp"

class A2D_API DynamicBody : public Body {
public:

	
	DynamicBody();
	DynamicBody(Image* im, BodyRectangle* rect);
	virtual void update(float gravity=0) override;

	Vecf accel;
	Vecf vel;
};
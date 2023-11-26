#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"

class A2D_API DynamicBody : public Body {
public:

	void update(float gravity=0) override;

	float accel_x = 0;
	float accel_y = 0;
	float vel_x = 0;
	float vel_y = 0;
};
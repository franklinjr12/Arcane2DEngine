#pragma once

#include "Arcane2DLib.hpp"
#include "Object.hpp"

#include "Animation.hpp"

class A2D_API UiComponent : public Object {
public:

	virtual void on_click() {};
	virtual void mouse_over() {};

	bool should_draw = true;
	Vecf pos;
	float w, h;
	Image* image;
	BodyRectangle* rect;
	Animation* animation;
};
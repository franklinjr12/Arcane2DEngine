#pragma once

#include "Arcane2DLib.hpp"
#include "Object.hpp"
#include "BodyRectangle.hpp"
#include "Animation.hpp"

class A2D_API UiComponent : public Object {
public:

	virtual void on_click() {};
	virtual void mouse_over() {};
	void resize(int new_w, int new_h) {
		rect->w = new_w;
		rect->h = new_h;
		image->resize(new_w, new_h);
	}

	bool should_draw = true;
	Vecf pos;
	float w, h;
	Image* image;
	BodyRectangle* rect;
	Animation* animation;
};
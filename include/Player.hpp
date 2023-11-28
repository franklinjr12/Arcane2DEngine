#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"
#include "EventHandler.hpp"
#include "Animation.hpp"
#include "DynamicBody.hpp"

class A2D_API Player : public DynamicBody {
public:
	Player(){
	}
	Player(Image* im, BodyRectangle* rect) : DynamicBody(im, rect) {
		image = im;
		rectangle = rect;
	}
	void _update() override;
	void process_events(std::vector<event_bytes_type> data);
	EventHandler handler;
	Animation animation;
};
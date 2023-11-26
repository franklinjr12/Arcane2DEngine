#pragma once

#include "Arcane2DLib.hpp"
#include "Body.hpp"
#include "EventHandler.hpp"
#include "Animation.hpp"

class A2D_API Player {
public:
	Player(Body& body) : body(body) {
	}
	void draw();
	void update();
	void process_events(std::vector<event_bytes_type> data);
	Body body;
	EventHandler handler;
	Animation animation;
};
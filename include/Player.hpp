#pragma once

#include "Body.hpp"
#include "EventHandler.hpp"
#include "Animation.hpp"

class Player {
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
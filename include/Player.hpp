#pragma once

#include "Body.hpp"
#include "EventHandler.hpp"


class Player {
public:
	Player(Body& body) : body(body) {
	}

	void process_keyboard(std::vector<event_bytes_type> data) {
		if (data[0] == (event_bytes_type)EventType::KeyboardInput) {
			switch (data[1]) {
			case GLFW_KEY_RIGHT:
				body.setX(body.getX() + 5);
					break;
			case GLFW_KEY_LEFT:
				body.setX(body.getX() - 5);
				break;

			case GLFW_KEY_DOWN:
				body.setY(body.getY() + 5);
				break;

			case GLFW_KEY_UP:
				body.setY(body.getY() - 5);
				break;
			}
		}
	}
	Body body;
	EventHandler handler;
};
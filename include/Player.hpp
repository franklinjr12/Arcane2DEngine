#pragma once

#include "Body.hpp"
#include "EventHandler.hpp"


class Player {
public:
	Player(Body& body, EventHandler& handler) : body(body), handler(handler) {}
	void process_keyboard(std::vector<uint8_t> data) {
		if (data[0] == (uint8_t)EventType::KeyboardInput) {
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
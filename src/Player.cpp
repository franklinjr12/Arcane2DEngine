#include "Player.hpp"

void Player::process_events(std::vector<event_bytes_type> data) {
	switch (data[0]) {
	case (event_bytes_type)EventType::KeyboardInput:
		// if (action == GLFW_PRESS) printf("key %d scancode %d name '%s'\n", key, scancode, key_name);
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
		default:
			break;
		}
	default:
		break;
	}
}

void Player::draw() {
	body.draw();
}

void Player::update() {
	if (animation.has_animation()) {
		animation.next_frame();
		body.image.texture_id = animation.images[animation.current_frame]->texture_id;
	}
	body.update();
}


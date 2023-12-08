#include "Scene.hpp"
#include "Collisions.hpp"
#include "Logger.hpp"

Scene::Scene(Camera* camera, Image* background, uint32_t w, uint32_t h) : camera(camera), background(background), w(w), h(h) {}

void Scene::update() {
	for (auto it = bodies.begin(); it != bodies.end(); it++) {
		Body* body = *it;
		if (body->suffer_gravity)
			body->update(gravity);
		else
			body->update();
		// TODO check if there is a better way to check collisions
		if (body->can_collide) {
			for (auto it_inner = bodies.begin(); it_inner != bodies.end(); it_inner++) {
				Body* body_inner = *it_inner;
				if (body_inner->can_collide) {
					if (isRectColliding(*body->rectangle, *body_inner->rectangle)) {
						if (body != body_inner) { // don't check collision with self
							body->collided = true;
							body_inner->collided = true;
							body->handle_collision(body_inner->id);
						}
					}
				}
			}
		}
	}
}

void Scene::draw() {
	if(background)
		background->draw(Vecf{ camera->rect.pos.x, camera->rect.pos.y }, background->width, background->height);
	for (auto it = bodies.begin(); it != bodies.end(); it++) {
		Body* body = *it;
		body->draw();
	}
}

void Scene::add_body(Body* body) {
	A2D_LOGI("body {} added", body->id);
	bodies.push_front(body);
	bodies_map[body->id] = body;
}

Body* Scene::get_body(ObjectId id) {
	return bodies_map[id];
}

Body* Scene::remove_body(ObjectId id) {
	A2D_LOGI("body {} removed", id);
	auto prev = bodies.before_begin();
	auto current = bodies.begin();

	while (current != bodies.end()) {
		if ((*current)->id == id) {
			// Body with the specified ID found

			// Remove the body from the 'bodies' container
			current = bodies.erase_after(prev);

			// Remove the body from the 'bodies_map' container
			auto it = bodies_map.find(id);
			if (it != bodies_map.end()) {
				bodies_map.erase(it);
			}

			if (current == bodies.end()) return nullptr;
			return *current; // Return a pointer to the removed body
		}

		++prev;
		++current;
	}

	// Body with the specified ID not found
	return nullptr;
}
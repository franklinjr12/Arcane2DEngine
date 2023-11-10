#include "Scene.hpp"

Scene::Scene(Camera& camera, Body& player, uint32_t w, uint32_t h) : camera(camera), player(player), w(w), h(h) {}

void Scene::update() {
	for (auto& body : bodies) {
		body->update(gravity);
	}
}

void Scene::draw() {
	for (Body* body : bodies) {
		if (isRectColliding(camera.rect, body->rectangle))
		{
			BodyRectangle rect = body->rectangle;
			body->rectangle.x -= camera.rect.x;
			body->rectangle.y -= camera.rect.y;
			body->draw();
			body->rectangle = rect;
		}
	}
	for (Surface* surface : surfaces) {
		if (isRectColliding(camera.rect, surface->body.rectangle))
		{
			BodyRectangle rect = surface->body.rectangle;
			surface->body.rectangle.x -= camera.rect.x;
			surface->body.rectangle.y -= camera.rect.y;
			surface->draw();
			surface->body.rectangle = rect;
		}
	}
	for (Button* button : buttons) {
		if (button->should_draw) {
			BodyRectangle rect = button->rect;
			button->rect.x += camera.rect.x;
			button->rect.y += camera.rect.y;
			button->draw();
			button->rect = rect;
		}
	}
}
void Scene::move_player(int x, int y) {
	player.setX(player.getX() + x);
	player.setY(player.getY() + y);
}
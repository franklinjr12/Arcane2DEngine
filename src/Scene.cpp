#include "Scene.hpp"
#include <algorithm>

Scene::Scene(Camera& camera, Body& player, Image& background, uint32_t w, uint32_t h) : camera(camera), player(player), background(background), w(w), h(h) {}

void Scene::update() {
	if (player.suffer_gravity)
		player.update(gravity);
	else
		player.update();
	for (auto it = bodies.begin(); it != bodies.end(); ++it) {
		(*it)->update(gravity);
		if ((*it)->getX() > w || (*it)->getX() < 0 ||
			(*it)->getY() > h || (*it)->getY() < 0) {
			bodies.erase(it);
		}
		// check particle collision
		if ((*it)->can_collide) {
			std::vector<Particle*> remove;
			for (auto it_p = particles.begin(); it_p != particles.end(); ++it_p) {
				if (isRectColliding((*it)->rectangle, (*it_p)->body.rectangle)) {
					// TODO have a interaction system with particle
					(*it_p)->should_erase = true;
				}
				if (isRectColliding(player.rectangle, (*it_p)->body.rectangle)) {
					// TODO have a interaction system with particle
					(*it_p)->should_erase = true;
				}
				if ((*it_p)->should_erase) {
					remove.push_back(*it_p);
				}
			}
			for (auto it = remove.begin(); it != remove.end(); ++it)
				particles.erase(std::remove(particles.begin(), particles.end(), *it), particles.end());
		}
	}
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		if ((*it)->body.suffer_gravity)
			(*it)->body.update(gravity);
		else
			(*it)->body.update();
		if ((*it)->body.getX() > w || (*it)->body.getX() < 0 ||
			(*it)->body.getY() > h || (*it)->body.getY() < 0) {
			particles.erase(it);
		}
	}

}

void Scene::draw() {
	background.draw(camera.rect.x, camera.rect.y);
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
	for (Particle* particle : particles) {
		BodyRectangle rect = particle->body.rectangle;
		particle->body.rectangle.x -= camera.rect.x;
		particle->body.rectangle.y -= camera.rect.y;
		particle->body.draw();
		particle->body.rectangle = rect;
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
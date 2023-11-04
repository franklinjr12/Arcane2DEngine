#include "Scene.hpp"

Scene::Scene(Camera& camera, uint32_t w, uint32_t h) : camera(camera), w(w), h(h) {}

void Scene::draw() {
	for (auto& body : bodies) {
		if (isRectColliding(camera.rect, body.rectangle))
		{
			BodyRectangle rect = body.rectangle;
			body.rectangle.x -= camera.rect.x;
			body.rectangle.y -= camera.rect.y;
			body.draw();
			body.rectangle = rect;
		}
	}
	// check for surfaces
	for (auto& surface : surfaces) {
		if (isRectColliding(camera.rect, surface.body.rectangle))
		{
			BodyRectangle rect = surface.body.rectangle;
			surface.body.rectangle.x -= camera.rect.x;
			surface.body.rectangle.y -= camera.rect.y;
			surface.draw();
			surface.body.rectangle = rect;
		}
	}
}
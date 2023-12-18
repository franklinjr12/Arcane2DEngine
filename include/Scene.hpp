#pragma once

#include "Arcane2DLib.hpp"
#include "Camera.hpp"
#include "Body.hpp"
#include "Particle.hpp"
#include "UiComponent.hpp"

#include <vector>
#include <forward_list>
#include <unordered_map>

class A2D_API Scene : public Object {
public:

	Scene(Camera* camera, Image* background, uint32_t w, uint32_t h);
	void draw() override;
	void update(Veci mouse_pos);
	void resolution_changed(int new_width, int new_height);
	void process_events(std::vector<event_bytes_type> data) override;
	void add_body(Body* body);
	Body* get_body(ObjectId id);
	Body* remove_body(ObjectId id);
	Camera* camera;
	Image* background;
	uint32_t w, h;
	float gravity = 0.1f;

	std::forward_list<Body*> bodies;
	std::forward_list<UiComponent*> uis;
	std::unordered_map<ObjectId, Body*> bodies_map;
};
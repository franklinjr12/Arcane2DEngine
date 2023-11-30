#pragma once

#include "Arcane2DLib.hpp"
#include "Camera.hpp"
#include "Body.hpp"
#include "Particle.hpp"
#include "Button.hpp"
#include <vector>
#include <forward_list>
#include <unordered_map>

class A2D_API Scene : public Object {
public:

	Scene(Camera* camera, Image* background, uint32_t w, uint32_t h);
	void draw();
	void update();
	void add_body(Body* body);
	Body* get_body(ObjectId id);
	Body* remove_body(ObjectId id);
	Camera* camera;
	Image* background;
	uint32_t w, h;
	float gravity = 0.1f;

	std::forward_list<Body*> bodies;
	std::unordered_map<ObjectId, Body*> bodies_map;
};
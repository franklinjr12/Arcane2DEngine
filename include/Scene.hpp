#pragma once

#include "Camera.hpp"
#include "Body.hpp"
#include "Surface.hpp"
#include "Button.hpp"
#include <vector>

class Scene {
public:
	Scene(Camera& camera, Body& player, uint32_t w, uint32_t h);
	void draw();
	void update();
	void move_player(int x, int y);
	Camera& camera;
	Body& player;
	std::vector<Body*> bodies;
	std::vector<Surface*> surfaces;
	std::vector<Button*> buttons;
	uint32_t w, h;
	float gravity = 0.1f;
};
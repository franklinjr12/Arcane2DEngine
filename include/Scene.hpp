#pragma once

#include "Arcane2DLib.hpp"
#include "Camera.hpp"
#include "DynamicBody.hpp"
#include "Particle.hpp"
#include "Surface.hpp"
#include "Button.hpp"
#include <vector>

class A2D_API Scene {
public:
	Scene(Camera& camera, DynamicBody* player, Image& background, uint32_t w, uint32_t h);
	void draw();
	void update();
	Camera& camera;
	DynamicBody* player;
	Image& background;
	std::vector<Body*> bodies;
	std::vector<Particle*> particles;
	std::vector<Surface*> surfaces;
	std::vector<Button*> buttons;
	uint32_t w, h;
	float gravity = 0.1f;
};
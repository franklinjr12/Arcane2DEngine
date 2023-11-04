#pragma once

#include "Camera.hpp"
#include "Body.hpp"
#include "Surface.hpp"
#include <vector>

class Scene {
public:
	Scene(Camera& camera, uint32_t w, uint32_t h);
	void draw();
	Camera camera;
	std::vector<Body> bodies;
	std::vector<Surface> surfaces;
	uint32_t w, h;
};
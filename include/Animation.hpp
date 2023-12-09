#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"

#include <vector>
#include <chrono>

class A2D_API Animation {
public:
	Animation();
	bool has_animation();
	void next_frame();
	void add_animation(Image& img);
	int current_frame = 0;
	std::vector<Image*> images;
	int fps = 1;
	std::chrono::system_clock::time_point last_time;
};
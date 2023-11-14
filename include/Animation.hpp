#pragma once

#include "Image.hpp"
#include <vector>
#include <chrono>

class Animation {
public:
	Animation(){ last_time = std::chrono::system_clock::now(); }
	bool has_animation() { return images.size(); }
	void next_frame() {
		auto diff = std::chrono::system_clock::now() - last_time;
		auto count = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
		if (count == 0) return;
		if ((1000 / count) > fps)
			return;
		last_time = std::chrono::system_clock::now();
		current_frame++;
		if (current_frame >= images.size())
			current_frame = 0;
	}
	void add_animation(Image& img) {
		images.push_back(&img);
	}
	int current_frame = 0;
	std::vector<Image*> images;
	int fps = 1;
	std::chrono::system_clock::time_point last_time;
};
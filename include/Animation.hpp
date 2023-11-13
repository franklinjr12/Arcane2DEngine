#pragma once

#include "Image.hpp"
#include <vector>

class Animation {
public:
	Animation(){}
	bool has_animation() { return images.size(); }
	void next_frame() {
		current_frame++;
		if (current_frame >= images.size())
			current_frame = 0;
	}
	void add_animation(Image& img) {
		images.push_back(&img);
	}
	int current_frame = 0;
	std::vector<Image*> images;
};
#include "Animation.hpp"

Animation::Animation() {
	last_time = std::chrono::system_clock::now();
}

bool Animation::has_animation() {
	return images.size();
}

void Animation::next_frame() {
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

void Animation::add_animation(Image& img) {
	images.push_back(&img);
}
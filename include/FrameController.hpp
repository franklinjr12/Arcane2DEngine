#pragma once

#include <chrono>
#include <thread>

struct FramesController {
	FramesController(int fps) : fps(fps) {
	}
	void frameBegin() {
		frame_begin = std::chrono::system_clock::now();
	}
	void frameEnd() {
		frame_end = std::chrono::system_clock::now();
	}
	void sleep() {
		auto diff = frame_end - frame_begin;
		frame_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
		auto sleep_time = 1000 / fps - frame_ms;
		if (sleep_time > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		}
	}
	int fps = 0;
	long long frame_ms = 0;
	std::chrono::system_clock::time_point frame_begin;
	std::chrono::system_clock::time_point frame_end;
};
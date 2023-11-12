#pragma once

#include <vector>

enum class EventType {
	KeyboardInput,
	MouseInput
};

struct EventData {
	EventType type;
	std::vector<uint8_t> data;
};
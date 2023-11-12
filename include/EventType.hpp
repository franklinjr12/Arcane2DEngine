#pragma once

#include <vector>

enum class EventType {
	KeyboardInput,
	MouseInput
};

typedef uint32_t event_bytes_type;

struct EventData {
	EventType type;
	std::vector<event_bytes_type> data;
};
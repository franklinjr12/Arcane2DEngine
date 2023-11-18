#pragma once

#include "Arcane2DLib.hpp"
#include <vector>

enum class A2D_LIB EventType {
	KeyboardInput,
	MouseInput
};

typedef uint32_t event_bytes_type;

struct A2D_LIB EventData {
	EventType type;
	std::vector<event_bytes_type> data;
};
#pragma once

#include "Arcane2DLib.hpp"
#include "EventType.hpp"
#include <functional>
#include <vector>

class A2D_API EventHandler {
public:
	std::function<void(std::vector<event_bytes_type>)> callback;
};
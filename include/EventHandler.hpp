#pragma once

#include "EventType.hpp"
#include <functional>
#include <vector>

class EventHandler {
public:
	std::function<void(std::vector<uint8_t>)> callback;
};
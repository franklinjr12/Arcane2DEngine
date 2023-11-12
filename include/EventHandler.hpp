#pragma once

#include "EventType.hpp"
#include <functional>
#include <vector>

class EventHandler {
public:
	std::function<void(std::vector<event_bytes_type>)> callback;
};
#pragma once

#include "EventType.hpp"
#include "EventHandler.hpp"

#include <queue>
#include <unordered_map>
#include <vector>

class EventsManager {
public:
	EventsManager();
	void run();
	void subscribe(EventType evt, EventHandler& handler);
	void unsubscribe(EventType evt, EventHandler& handler);
	std::queue<EventData> events_data;
	std::unordered_map<EventType, std::vector<EventHandler*>> subscribers;
};
#pragma once

#include "Arcane2DLib.hpp"
#include "EventType.hpp"
#include "Object.hpp"

#include <queue>
#include <unordered_map>
#include <vector>

class A2D_API EventsManager {
public:
	EventsManager();
	void run();
	void subscribe(EventType evt, Object* obj);
	void unsubscribe(EventType evt, Object* obj);
	void subscribe(std::string evt_name, Object* obj);
	void unsubscribe(std::string evt_name, Object* obj);
	std::queue<EventData> events_data;
	std::queue<CustomEventData> custom_events_data;
	std::unordered_map<std::string, std::vector<Object*>> custom_subscribers;
	std::unordered_map<EventType, std::vector<Object*>> subscribers;
};
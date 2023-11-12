#include "EventsManager.hpp"
#include <iostream>


EventsManager::EventsManager() {}

void EventsManager::run() {
	while (true) {
		while (!events_data.empty()) {
			auto& evt = events_data.front();
			auto& v = subscribers[evt.type];
			for (int i = 0; i < v.size(); i++)
				v[i]->callback(evt.data);
			events_data.pop();
		}
	}
}

void EventsManager::subscribe(EventType evt, EventHandler& handler) {
	subscribers[evt].push_back(&handler);
}

void EventsManager::unsubscribe(EventType evt, EventHandler& handler) {
	auto v = subscribers[evt];
	auto it = v.begin();
	for (int i = 0; i < v.size(); i++, it++)
		if (v[i] == &handler)
			v.erase(it);
}

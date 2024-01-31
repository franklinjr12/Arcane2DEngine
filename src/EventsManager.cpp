#include "EventsManager.hpp"
#include "Logger.hpp"

#include <iostream>

void EventsManager::run() {
	while (!events_data.empty()) {
		auto& evt = events_data.front();
		if (&evt != NULL) {
			auto& v = subscribers[evt.type];
			for (int i = 0; i < v.size(); i++) {
				// this is a workaround, but no events should have empty data
				if (!evt.data.empty()) {
					A2D_LOGI("Object {} processing evt {}", v[i]->id, (int)evt.type);
					v[i]->process_events(evt.data);
				}
			}
			events_data.pop();
		}
	}
	while (!custom_events_data.empty()) {
		auto& cevt = custom_events_data.front();
		auto& v = custom_subscribers[cevt.name];
		for (int i = 0; i < v.size(); i++) {
			A2D_LOGI("Object {} processing cevt {}", v[i]->id, cevt.name);
			v[i]->process_events(cevt.data);
		}
		custom_events_data.pop();
	}
}

void EventsManager::subscribe(EventType evt, Object* obj) {
	A2D_LOGI("Object {} subscribed to {}", obj->id, (int)evt);
	subscribers[evt].push_back(obj);
}

void EventsManager::unsubscribe(EventType evt, Object* obj) {
	A2D_LOGI("Object {} unsubscribed to {}", obj->id, (int)evt);
	auto v = subscribers[evt];
	auto it = v.begin();
	for (int i = 0; i < v.size(); i++, it++)
		if (v[i] == obj)
			v.erase(it);
}

void EventsManager::subscribe(std::string evt_name, Object* obj) {
	A2D_LOGI("Object {} subscribed to {}", obj->id, evt_name);
	custom_subscribers[evt_name].push_back(obj);
}

void EventsManager::unsubscribe(std::string evt_name, Object* obj) {
	A2D_LOGI("Object {} unsubscribed to {}", obj->id, evt_name);
	auto v = custom_subscribers[evt_name];
	auto it = v.begin();
	for (int i = 0; i < v.size(); i++, it++)
		if (v[i] == obj)
			v.erase(it);
}

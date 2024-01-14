#include "Timer.hpp"

#include <EventsManager.hpp>
#include <cstdio>

using namespace std::chrono;

Timer::Timer(uint64_t timeout_ms, bool repeat) {
	char buffer[21];
	sprintf_s(buffer, 21, "%lu", (uint64_t)id);
	name = "timer" + std::string(buffer);
	should_repeat = repeat;
	timeout = timeout_ms * 1ms;
	current = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

void Timer::start() {
	if (!t) {
		t = new std::thread(timer_thread, this);
	}
}

void Timer::stop() {
	delete t;
}

void Timer::reset(){
	current = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	if (!t) {
		t = new std::thread(timer_thread, this);
	}
}

void timer_thread(Timer* timer) {
	while (true) {
		auto now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		auto diff = now - timer->current;
		if (diff >= timer->timeout) {
		//if (now - timer->current >= timer->timeout) {
			EventData ed;
			ed.type = EventType::Timer;
			ed.data.push_back((event_bytes_type)EventType::Timer);
			ed.data.push_back(static_cast<event_bytes_type>(timer->name.size()));
			for (auto& e : timer->name)
				ed.data.push_back(static_cast<event_bytes_type>(e));
			EventsManager::getInstance()->events_data.push(ed);
			if (timer->should_repeat)
				timer->current = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			else {
				//delete timer->t;
				break;
			}
		}
	}
}
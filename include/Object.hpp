#pragma once

#include "Arcane2DLib.hpp"
#include "ArcaneTypes.hpp"
#include "IdGenerator.hpp"
#include "EventType.hpp"

#include <string>
#include <vector>

class A2D_API Object {
public:
	Object() { id = generate_id(); }
	virtual void process_events(std::vector<event_bytes_type> data) {};
	virtual void draw() {};
	virtual void _draw() {};
	virtual void update() {};
	virtual void _update() {};
	ObjectId id;
	std::vector<ObjectGroup> groups;
	std::string name;
};
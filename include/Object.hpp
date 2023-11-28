#pragma once

#include "Arcane2DLib.hpp"
#include "ArcaneTypes.hpp"
#include "IdGenerator.hpp"

#include <string>
#include <vector>

class A2D_API Object {
public:
	Object() { id = generate_id(); }
	ObjectId id;
	std::vector<ObjectGroup> groups;
	std::string name;
};
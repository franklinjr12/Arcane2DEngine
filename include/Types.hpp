#pragma once

#include "Arcane2DLib.hpp"

#include <cstdlib>

typedef int Veci[2];

typedef float Vecf[2];

struct Point {
	union {
		struct {
			float x, y;
		};
		Vecf pos;
	};
};

typedef uint32_t ObjectId;
typedef uint32_t ObjectGroup;

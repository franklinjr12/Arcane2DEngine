#include "Collisions.hpp"

bool Collisions::isRectColliding(BodyRectangle& a, BodyRectangle& b) {
	// Check if one rectangle is to the left of the other
	if (a.x + a.w < b.x || b.x + b.w < a.x) {
		return false;
	}
	// Check if one rectangle is above the other
	if (a.y + a.h < b.y || b.y + b.h < a.y) {
		return false;
	}
	// If neither of the above are true, then the rectangles are overlapping
	return true;
}

bool Collisions::isPointRectColliding(BodyRectangle& a, int x, int y) {
	// Check if one rectangle is to the left of the other
	if (a.x + a.w < x || x < a.x) {
		return false;
	}
	// Check if one rectangle is above the other
	if (a.y + a.h < y || y < a.y) {
		return false;
	}
	// If neither of the above are true, then the rectangles are overlapping
	return true;
}
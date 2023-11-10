#pragma once


class BodyRectangle {
public:
	BodyRectangle(int x, int y, int width, int height);
	int x,y, w, h;
};

bool isRectColliding(BodyRectangle& a, BodyRectangle& b);
bool isPointRectColliding(BodyRectangle& a, int x, int y);
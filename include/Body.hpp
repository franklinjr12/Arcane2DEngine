#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "Object.hpp"
#include "Types.hpp"

class A2D_API Body : public Object {
public:
	
	Body();
	Body(Image* im, BodyRectangle* rect);
	~Body();
	virtual void draw();
	virtual void draw(int w, int h);
	virtual void update(float gravity = 0);
	virtual void handle_collision(ObjectId id) {};
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();

	Image* image = nullptr;
	BodyRectangle* rectangle = nullptr;
	bool can_collide = true;
	bool draw_rect_overlay = false;

protected:

	Point pos;
};
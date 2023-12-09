#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "Object.hpp"
#include "ArcaneTypes.hpp"

class A2D_API Body : public Object {
public:
	
	Body();
	Body(Image* im, BodyRectangle* rect);
	~Body();
	virtual void draw() override;
	virtual void draw(int w, int h);
	virtual void update(float gravity = 0);
	virtual void handle_collision(ObjectId _id) {};
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();

	Image* image = nullptr;
	BodyRectangle* rectangle = nullptr;
	bool can_collide = true;
	bool collided = false;
	bool suffer_gravity = false;
	bool draw_rect_overlay = false;
	bool should_delete = false;

protected:

	Point pos;
};
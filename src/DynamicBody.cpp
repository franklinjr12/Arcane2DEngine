#include "DynamicBody.hpp"

DynamicBody::DynamicBody() {
	accel[0] = 0;
	accel[1] = 0;
	vel[0] = 0;
	vel[1] = 0;
}

DynamicBody::DynamicBody(Image* im, BodyRectangle* rect) : Body(im, rect) {
	accel[0] = 0;
	accel[1] = 0;
	vel[0] = 0;
	vel[1] = 0;
}


void DynamicBody::update(float gravity) {
	vel[0] += accel[0];
	//vel[1] += accel[1];
	pos.x += vel[0];
	if (suffer_gravity)
		vel[1] += accel[1] + gravity;
	else
		vel[1] += accel[1];
	pos.y += vel[1];
	rectangle->pos.x = pos.x;
	rectangle->pos.y = pos.y;
	_update();
}
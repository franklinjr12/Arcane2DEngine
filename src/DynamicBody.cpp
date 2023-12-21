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

std::vector<char> DynamicBody::serialize() {
	std::vector<char> v;
	const char* ptr = reinterpret_cast<const char*>(&id);
	v.insert(v.end(), ptr, ptr + sizeof(ObjectId));
	//add number of groups
	v.push_back((char)groups.size());
	for (auto& e : groups) {
		const char* group_ptr = reinterpret_cast<const char*>(&e);
		v.insert(v.end(), group_ptr, group_ptr + sizeof(ObjectGroup));
	}
	v.insert(v.end(), name.begin(), name.end());
	auto ser_img = image->serialize();
	size_t ser_img_size = ser_img.size();
	ptr = reinterpret_cast<const char*>(&ser_img_size);
	v.insert(v.end(), ptr, ptr + sizeof(ser_img_size));
	v.insert(v.end(), ser_img.begin(), ser_img.end());
	auto ser_rect = rectangle->serialize();
	size_t ser_rect_size = ser_rect.size();
	ptr = reinterpret_cast<const char*>(&ser_img_size);
	v.insert(v.end(), ptr, ptr + sizeof(ser_img_size));
	ptr = reinterpret_cast<const char*>(&accel);
	v.insert(v.end(), ptr, ptr + sizeof(accel));
	ptr = reinterpret_cast<const char*>(&vel);
	v.insert(v.end(), ptr, ptr + sizeof(vel));
	ptr = reinterpret_cast<const char*>(&pos);
	v.insert(v.end(), ptr, ptr + sizeof(pos));
	ptr = reinterpret_cast<const char*>(&can_collide);
	v.insert(v.end(), ptr, ptr + sizeof(can_collide));
	ptr = reinterpret_cast<const char*>(&suffer_gravity);
	v.insert(v.end(), ptr, ptr + sizeof(suffer_gravity));
	ptr = reinterpret_cast<const char*>(&draw_rect_overlay);
	v.insert(v.end(), ptr, ptr + sizeof(draw_rect_overlay));
	return v;
}


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

DynamicBody::DynamicBody(std::vector<char>& serialized_data) {
	id = *reinterpret_cast<const ObjectId*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(ObjectId));
	int bytes_size = serialized_data.front();
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + 1);
	for (int i = 0; i < bytes_size; i++) {
		ObjectGroup og = id = *reinterpret_cast<const ObjectGroup*>(&serialized_data[i * sizeof(ObjectGroup)]);
		groups.push_back(og);
	}
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size * sizeof(ObjectGroup));
	bytes_size = serialized_data.front();
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + 1);
	for (int i = 0; i < bytes_size; i++) {
		name += serialized_data.front();
		serialized_data.erase(serialized_data.begin(), serialized_data.begin() + 1);
	}
	bytes_size = serialized_data.front();
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + 1);
	std::vector<char> ser_img(serialized_data.begin(), serialized_data.begin() + bytes_size);
	image = new Image(ser_img);
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size);
	bytes_size = serialized_data.front();
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + 1);
	std::vector<char> ser_rect(serialized_data.begin(), serialized_data.begin() + bytes_size);
	rectangle = new BodyRectangle(ser_rect);
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size);
	accel[0] = *reinterpret_cast<const Vecf*>(serialized_data.data())[0];
	accel[1] = *reinterpret_cast<const Vecf*>(serialized_data.data())[1];
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(Vecf));
	vel[0] = *reinterpret_cast<const Vecf*>(serialized_data.data())[0];
	vel[1] = *reinterpret_cast<const Vecf*>(serialized_data.data())[1];
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(Vecf));
	pos = *reinterpret_cast<const Point*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(Point));
	can_collide = *reinterpret_cast<const bool*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(bool));
	suffer_gravity = *reinterpret_cast<const bool*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(bool));
	draw_rect_overlay = *reinterpret_cast<const bool*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(bool));
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
	v.push_back(name.size());
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


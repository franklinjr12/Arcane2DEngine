#pragma once

#include "Arcane2DLib.hpp"
#include "Object.hpp"
#include "BodyRectangle.hpp"
#include "Animation.hpp"

class A2D_API UiComponent : public Object {
public:

	UiComponent(){}
	//UiComponent(std::vector<char>& serialized_data) : Object(serialized_data) {

	//	
	//}
	//std::vector<char> serialize() {
	//	std::vector<char> v = Object::serialize();
	//	auto ser_img = image->serialize();
	//	size_t ser_img_size = ser_img.size();
	//	const char* ptr = reinterpret_cast<const char*>(&ser_img_size);
	//	v.insert(v.end(), ptr, ptr + sizeof(ser_img_size));
	//	v.insert(v.end(), ser_img.begin(), ser_img.end());
	//	auto ser_rect = rect->serialize();
	//	size_t ser_rect_size = ser_rect.size();
	//	ptr = reinterpret_cast<const char*>(&ser_img_size);
	//	v.insert(v.end(), ptr, ptr + sizeof(ser_img_size));
	//	ptr = reinterpret_cast<const char*>(&pos);
	//	v.insert(v.end(), ptr, ptr + sizeof(pos));
	//}
	std::vector<char> serialize() {
		std::vector<char> v = Object::serialize();
		auto ser_img = image->serialize();
		size_t ser_img_size = ser_img.size();
		const char* ptr = reinterpret_cast<const char*>(&ser_img_size);
		v.insert(v.end(), ptr, ptr + sizeof(ser_img_size));
		v.insert(v.end(), ser_img.begin(), ser_img.end());
		auto ser_rect = rect->serialize();
		size_t ser_rect_size = ser_rect.size();
		ptr = reinterpret_cast<const char*>(&ser_img_size);
		v.insert(v.end(), ptr, ptr + sizeof(ser_img_size));
		auto ser_animation = animation->serialize();
		size_t ser_animation_size = ser_animation.size();
		ptr = reinterpret_cast<const char*>(&ser_animation_size);
		v.insert(v.end(), ptr, ptr + sizeof(ser_animation_size));
		ptr = reinterpret_cast<const char*>(&pos);
		v.insert(v.end(), ptr, ptr + sizeof(pos));
		ptr = reinterpret_cast<const char*>(&should_draw);
		v.insert(v.end(), ptr, ptr + sizeof(should_draw));
		ptr = reinterpret_cast<const char*>(&w);
		v.insert(v.end(), ptr, ptr + sizeof(w));
		ptr = reinterpret_cast<const char*>(&h);
		v.insert(v.end(), ptr, ptr + sizeof(h));
		return v;
	}
	virtual void on_click() {};
	virtual void mouse_over() {};
	void resize(int new_w, int new_h) {
		rect->w = new_w;
		rect->h = new_h;
		image->resize(new_w, new_h);
	}

	bool should_draw = true;
	Vecf pos;
	float w, h;
	Image* image;
	BodyRectangle* rect;
	Animation* animation;
};
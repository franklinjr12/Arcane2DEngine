#include "Button.hpp"

#include "EventsManager.hpp"
#include "Logger.hpp"

Button::Button(Vecf pos, Image* image, float width, float height, std::string text) {
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->image = image;
	this->text = text;
	if (width > 0 && height > 0) {
		w = width;
		h = height;
		rect = new BodyRectangle(pos, w, h);
	}
	else {
		w = image->width;
		h = image->height;
		rect = new BodyRectangle(pos, w, h);
	}
}

void Button::draw() {
	if (should_draw) {
		image->draw(pos, w, h);
	}
}

void Button::on_click() {
	A2D_LOGI("Button {} clicked", id);
	EventData ed;
	ed.type = EventType::ButtonClicked;
	ed.data.push_back((event_bytes_type)ed.type);
	ed.data.push_back((event_bytes_type)id);
	EventsManager::getInstance()->events_data.push(ed);
}

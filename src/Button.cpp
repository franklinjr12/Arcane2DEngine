#include "Button.hpp"

Button::Button(float x, float y, float width, float height, std::string text, Image& image) : img(image), rect(Vecf{x,y}, width, height) {
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
	this->text = text;
}

void Button::draw() {
	if (should_draw)
		img.draw(Vecf{ x, y }, w, h);
}

void Button::update() {}

void Button::on_click(std::function<void()> callback) {
}

void Button::mouse_over() {
	callback();
}
#include "TextDisplay.hpp"

TextDisplay::TextDisplay(Vecf pos, Image* image, std::string text, Font* font) {
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->image = image;
	this->text = text;
	this->font = font;
	w = image->width;
	h = image->height;
	rect = new BodyRectangle(pos, w, h);
	font_pos[0] = pos[0];
	font_pos[1] = pos[1];
}

void TextDisplay::draw() {
	if (should_draw) {
		image->draw(pos, w, h);
		if (font != nullptr && text != "") {
			font->print(font_pos, (char*)text.c_str());
		}
	}
}
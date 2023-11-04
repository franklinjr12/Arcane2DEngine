#pragma once
#include <stb_image.h>

#include "Image.hpp"

Image::Image(std::string path, bool texture_clamp) {
	if (texture_clamp)
		texture_mode = GL_REPEAT;
	loadImage(path);
}
void Image::loadImage(std::string path) {
	if (texture_id != 0)
		glDeleteTextures(1, &texture_id);
	this->path = path;
	int nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		if (nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else {
			std::cerr << "Unsupported channel count: " << nrChannels << std::endl;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

}
void Image::draw(float x, float y) {
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x, height * 1.0f + y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width * 1.0f, height * 1.0f + y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width * 1.0f, y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
	glEnd();
}
void Image::draw(float x, float y, int w, int h) {
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(x, h * 1.0f + y);
	glTexCoord2f((w / width) * 1.0f, 0.0f); glVertex2f(x + w * 1.0f, h * 1.0f + y);
	glTexCoord2f((w / width) * 1.0f, (h / height) * 1.0f); glVertex2f(x + w * 1.0f, y);
	glTexCoord2f(0.0f, (h / height) * 1.0f); glVertex2f(x, y);
	glEnd();
}

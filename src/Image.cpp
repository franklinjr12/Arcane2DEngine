#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize2.h>
#include "Image.hpp"

Image::Image(std::string path, int custom_w, int custom_h, bool texture_clamp) {
	this->path = path;
	if (texture_clamp)
		texture_mode = GL_REPEAT;
	if (custom_w && custom_h)
		resize(custom_w, custom_h);
	else
		loadImage(path);
}
Image::~Image() {
	if (texture_id != 0)
		glDeleteTextures(1, &texture_id);

}
void Image::loadImage(std::string path) {
	if (texture_id != 0)
		glDeleteTextures(1, &texture_id);
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
		stbi_image_free(data);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
		std::cerr << stbi_failure_reason() << std::endl;
		
	}
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

void Image::resize(int neww, int newh) {
	if (texture_id != 0)
		glDeleteTextures(1, &texture_id);
	int nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	unsigned char* resized_data = new unsigned char[neww * newh * nrChannels];

	// Perform the resize
	if (data) {
		stbir_pixel_layout sp = STBIR_RGBA;
		if (nrChannels == 3) sp = STBIR_RGB;
		if (!stbir_resize_uint8_linear(data, width, height, 0, resized_data, neww, newh, 0, sp)) {
			std::cerr << "Failed to resize image" << std::endl;
		}
		stbi_image_free(data); // Free the original image data
		data = resized_data; // Point 'data' to the resized image data
		width = neww;
		height = newh;
	}
	else {
		std::cerr << "Failed to load texture" << std::endl;
	}


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

	stbi_image_free(resized_data);
}
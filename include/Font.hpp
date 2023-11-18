#pragma once

#include "Arcane2DLib.hpp"
#include "GL/glew.h"
#include <fstream>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

class A2D_LIB Font {
public:
	Font(std::string font_path = "assets/16020_FUTURAM.ttf", int font_size = 32);

	void print(float x, float y, char* text, float r = 0, float g = 0, float b = 0, float a = 1);

	unsigned char* font_ttf_buffer;
	unsigned char* font_temp_bitmap;
	stbtt_bakedchar font_cdata[96]; // ASCII 32..126 is 95 glyphs
	GLuint font_ftex;
};

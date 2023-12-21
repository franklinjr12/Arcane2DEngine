#pragma once

#include "Arcane2DLib.hpp"
#include "ArcaneTypes.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class A2D_API Image {
public:

    Image(std::string path, int custom_w=0, int custom_h=0, bool texture_clamp = false, bool flipv = true);
    Image(std::vector<char>& serialized_data);
    ~Image();
    void loadImage(std::string path, bool flipv = true);
    void draw(Vecf pos, int w = 1, int h = 1);
    void draw(Vecf pos, RGBA_t color, float w=1, float h=1);
    void resize(int neww, int newh, bool flipv = true);
    std::vector<char> serialize();

    std::string path;
    float width, height;
    GLuint texture_id = 0;
    GLint texture_mode = GL_CLAMP_TO_EDGE;
};

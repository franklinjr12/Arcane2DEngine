#pragma once

#include "Arcane2DLib.hpp"
#include "Types.hpp"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class A2D_API Image {
public:

    Image(std::string path, int custom_w=0, int custom_h=0, bool texture_clamp = false);
    ~Image();
    void loadImage(std::string path);
    void draw(Vecf pos);
    void draw(Vecf pos, int w, int h);
    void resize(int neww, int newh);

    std::string path;
    int width, height;
    GLuint texture_id = 0;
    GLint texture_mode = GL_CLAMP_TO_EDGE;
};

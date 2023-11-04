#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Image {
public:
    Image(std::string path, bool texture_clamp = false);
    void loadImage(std::string path);
    void draw(float x, float y);
    void draw(float x, float y, int w, int h);
    std::string path;
    int width, height;
    GLuint texture_id = 0;
    GLint texture_mode = GL_CLAMP_TO_EDGE;
};

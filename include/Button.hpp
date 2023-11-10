#pragma once

#include <string>
#include <functional>
#include "Image.hpp"
#include "BodyRectangle.hpp"

class Button {
public:
    Button(float x, float y, float width, float height, std::string text, Image& image);

    void draw();
    void update();
    void on_click(std::function<void()> callback);
    void mouse_over();

    float x, y, w, h;
    std::string text;
    bool should_draw = true;
    Image& img;
    BodyRectangle rect;
    std::function<void()> callback;
};

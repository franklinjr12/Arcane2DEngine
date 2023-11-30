#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "Object.hpp"

#include <string>
#include <functional>

class A2D_API Button : public Object {
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

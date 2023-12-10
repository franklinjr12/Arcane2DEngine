#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "UiComponent.hpp"
#include "Font.hpp"

class A2D_API Button : public UiComponent {
public:
    Button(Vecf pos, Image* image, float width=0, float height=0, std::string text="", Font* font=nullptr);

    void draw() override;
    void on_click() override;

    Font* font;
    Vecf font_pos;
    std::string text; //unused at the moment
};

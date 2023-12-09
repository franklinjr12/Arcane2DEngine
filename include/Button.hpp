#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "UiComponent.hpp"


class A2D_API Button : public UiComponent {
public:
    Button(Vecf pos, Image* image, float width=0, float height=0, std::string text="");

    void draw() override;
    void on_click() override;

    std::string text;
};

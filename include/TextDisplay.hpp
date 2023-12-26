#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "UiComponent.hpp"
#include "Font.hpp"

class A2D_API TextDisplay : public UiComponent {
public:
    TextDisplay(Vecf pos, Image* image, std::string text = "", Font* font=nullptr);
    TextDisplay(std::vector<char> serialized_data);

    std::vector<char> serialize();
    void draw() override;

    Vecf font_pos;
    Font* font;
    std::string text;
};

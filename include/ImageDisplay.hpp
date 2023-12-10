#pragma once

#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "UiComponent.hpp"
#include "Animation.hpp"


// will mainly be used with animation
class A2D_API ImageDisplay : public UiComponent {
public:
    ImageDisplay(Vecf pos, Image* image);

    void draw() override;
};
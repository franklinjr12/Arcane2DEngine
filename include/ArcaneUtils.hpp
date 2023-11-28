#pragma once

#include "Image.hpp"

const float OVERLAY_ALPHA = 0.2;

Image& GetBlueOverlayImage() {
    static Image blue_overlay("assets/blue_overlay.png");
    return blue_overlay;
}
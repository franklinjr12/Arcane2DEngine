#pragma once

#include "Image.hpp"
#include "Arcane2DLib.hpp"

// all game images are based on this resolution
#define DEFAULT_SCREEN_WIDTH 1920
#define DEFAULT_SCREEN_HEIGHT 1080

#define DEFAULT_FPS 30

const float OVERLAY_ALPHA = 0.2;

A2D_API Image& GetBlueOverlayImage();

A2D_API float DistanceVecf(Vecf v1, Vecf v2);

A2D_API float MagVecf(Vecf v);
#pragma once

#include "Image.hpp"
#include "Arcane2DLib.hpp"

const float OVERLAY_ALPHA = 0.2;

A2D_API Image& GetBlueOverlayImage();

A2D_API float DistanceVecf(Vecf v1, Vecf v2);

A2D_API float MagVecf(Vecf v);
#pragma once

#include "Image.hpp"

const float OVERLAY_ALPHA = 0.2;

Image& GetBlueOverlayImage() {
	static Image blue_overlay("assets/blue_overlay.png");
	return blue_overlay;
}

float DistanceVecf(Vecf v1, Vecf v2) {
	float a = v1[0] - v2[0];
	float b = v1[1] - v2[1];
	return sqrt(a * a + b * b);
}

float MagVecf(Vecf v) {
	return sqrt(v[0] * v[0] + v[1] * v[1]);
}
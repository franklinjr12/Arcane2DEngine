#include "Camera.hpp"
#include "ArcaneTypes.hpp"

Camera::Camera(int x, int y, int w, int h) : rect(Vecf{ (float)x, (float)y }, w, h) {}
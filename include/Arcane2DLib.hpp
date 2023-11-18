#pragma once

#ifdef ARCANE2D_COMPILE
#define A2D_LIB __declspec(dllexport)
#else
#define A2D_LIB __declspec(dllimport)
#endif
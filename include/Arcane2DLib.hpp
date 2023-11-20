#pragma once

#ifdef ARCANE2D_COMPILE
#define A2D_LIB __declspec(dllexport)
#else
#ifdef ARCANE2D_COMPILE_EXE
#define A2D_LIB 
#else
#define A2D_LIB __declspec(dllimport)
#endif
#endif
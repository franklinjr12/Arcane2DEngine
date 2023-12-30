#pragma once

#include "Arcane2DLib.hpp"
#include "FontsManager.hpp"

class A2D_API AssetsManager {
public:

	static AssetsManager& get_instance();
	static Font* get_default_font();

private:
	//static AssetsManager am;
	AssetsManager() {}
};
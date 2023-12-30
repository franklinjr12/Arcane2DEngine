#pragma once

#include "Arcane2DLib.hpp"
#include "FontsManager.hpp"
#include "Image.hpp"

#include <unordered_map>

class A2D_API AssetsManager {
public:

	static AssetsManager& get_instance();
	Font* get_default_font();
	Image* get_image(std::string asset_name);

private:
	//static AssetsManager am;
	AssetsManager() {}

	std::unordered_map<std::string, Image*> images_map;
};
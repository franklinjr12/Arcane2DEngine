#include "AssetsManager.hpp"

//AssetsManager::AssetsManager am;

AssetsManager& AssetsManager::get_instance() {
	static AssetsManager am;
	return am;
}

Font* AssetsManager::get_default_font() {
	return FontsManager::get_instance()->default_font;
}

Image* AssetsManager::get_image(std::string asset_name) {
	if (images_map.at(asset_name))
		return images_map.at(asset_name);
	Image* img = new Image("assets/" + asset_name);
	if (img) {
		images_map[asset_name] = img;
		return img;
	}
	return nullptr;
}
#include "AssetsManager.hpp"

//AssetsManager::AssetsManager am;

AssetsManager& AssetsManager::get_instance() {
	static AssetsManager am;
	return am;
}

Font* AssetsManager::get_default_font() {
	return FontsManager::get_instance()->default_font;
}

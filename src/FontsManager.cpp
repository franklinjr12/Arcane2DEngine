#include "FontsManager.hpp"

A2D_API FontsManager* FontsManager::get_instance() {
	static FontsManager fm;
	return &fm;
}
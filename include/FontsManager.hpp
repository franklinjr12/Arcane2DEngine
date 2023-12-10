#pragma once

#include "Arcane2DLib.hpp"
#include "Font.hpp"

class A2D_API FontsManager {
public:

	static FontsManager* get_instance();
	//	static FontsManager* get_instance() {
	//	static FontsManager fm;
	//	return &fm;
	//}

	Font* default_font;

private:

	FontsManager() {
		default_font = new Font();
	}
	FontsManager(const FontsManager&) = delete;
	FontsManager& operator=(const FontsManager&) = delete;
};

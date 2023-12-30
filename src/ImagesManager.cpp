#include "ImagesManager.hpp"

ImagesManager::ImagesManager() {

}

ImagesManager* ImagesManager::get_instance() {
	static ImagesManager im;
	return &im;
}

Image* ImagesManager::get_image(std::string img_name) {
	if (images_map.at(img_name))
		return images_map.at(img_name);
	Image* img = new Image("assets/" + img_name);
	if (img) {
		images_map[img_name] = img;
		return img;
	}
	return nullptr;
}

void ImagesManager::add_image(std::string img_name, Image* img) {
	images_map[img_name] = img;
}

Image* ImagesManager::remove_image(std::string img_name) {
	Image* img = images_map.at(img_name);
	if (img)
		images_map.erase(img_name);
	return img;
}

#include "ConfigurationManager.hpp"

#include <inicpp.h>


ConfigurationManager ConfigurationManager::self;

ConfigurationManager& ConfigurationManager::get_instance() {
	return self;
}

ConfigurationManager::ConfigurationManager() {
}

int ConfigurationManager::get_resolution_width() {
	ini::IniFile config;
	config.load(ini_path);
	return config["display"]["width"].as<int>();
}

int ConfigurationManager::get_resolution_height() {
	ini::IniFile config;
	config.load(ini_path);
	return config["display"]["height"].as<int>();
}

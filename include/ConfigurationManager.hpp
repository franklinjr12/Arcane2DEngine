#pragma once

#include <iostream>

class ConfigurationManager {
public:

	static ConfigurationManager& get_instance();
	int get_resolution_width();
	int get_resolution_height();

private:

	static ConfigurationManager self;
	ConfigurationManager();

	const std::string ini_path = "config.ini";
};
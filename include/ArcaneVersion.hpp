#pragma once

#include <iostream>
#include <cstdio>

#define MAJOR 0
#define MINOR 1
#define PATCH 0
#define BUILD 1

std::string arcane_version_string() {
	char b[128];
	sprintf(b, "%d.%d.%d.%d", MAJOR, MINOR, PATCH, BUILD);
	return std::string(b);
}
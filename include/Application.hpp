#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Image.hpp"
#include "FrameController.hpp"
#include "Body.hpp"
#include "Surface.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768


class Application {
public:
	Application(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
	// override this method and put 
	virtual void game_loop();

	// capture keyboard events
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	// Static trampoline function to the real member function callback
	static void KeyCallbackTrampoline(GLFWwindow* window, int key, int scancode, int action, int mods);
	void setWindowCallbacks(GLFWwindow* window);
	int init();
	void run();
	void poll_events();
	void update();
	void draw();
	void print_text(float x, float y, char* text, float r, float g, float b);
	// TODO compiel ImGui only on debug
	void handle_imgui();
	Scene* current_scene = nullptr;
	std::vector<Scene> scenes;
	std::map<uint32_t, GLFWkeyfun> key_callbacks;
	GLFWwindow* window = nullptr;
	int width, height;
	GLFWwindow* window_imgui = nullptr;
	double mouse_xpos, mouse_ypos;
};

static void glfw_error_callback(int error, const char* description) {
	std::cout << "GLFW Error: " << description << std::endl;
}

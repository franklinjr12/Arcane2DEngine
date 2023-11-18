#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "FrameController.hpp"
#include "Body.hpp"
#include "Surface.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Player.hpp"
#include "Particle.hpp"
#include "EventsManager.hpp"
#include "Button.hpp"
#include "Font.hpp"

#ifdef COMPILE_IMGUI
#define IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768


class A2D_LIB Application {
public:
	Application(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
	// override this method and put all your game inside
	virtual void game_loop();
	// if needed custom drawing put in here
	virtual void game_draw();

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
	Scene* current_scene = nullptr;
	std::vector<Scene> scenes;
	GLFWwindow* window = nullptr;
	int width, height;
#ifdef COMPILE_IMGUI
	void handle_imgui();
	GLFWwindow* window_imgui = nullptr;
#endif
	double mouse_xpos=0, mouse_ypos=0;
	EventsManager* events_manager;
	Player* player;
};

static void glfw_error_callback(int error, const char* description) {
	std::cout << "GLFW Error: " << description << std::endl;
}

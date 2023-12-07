#pragma once

#include <iostream>
#include "Arcane2DLib.hpp"
#include "Image.hpp"
#include "BodyRectangle.hpp"
#include "Body.hpp"
#include "FrameController.hpp"
#include "StaticBody.hpp"
#include "Camera.hpp"
#include "Collisions.hpp"
#include "Scene.hpp"
#include "Player.hpp"
#include "Particle.hpp"
#include "EventsManager.hpp"
#include "Button.hpp"
#include "Font.hpp"
#include "FrameController.hpp"
#include "Logger.hpp"

#ifdef COMPILE_IMGUI
#define IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define DEFAULT_FPS 30


class A2D_API Application {
public:
	Application(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
	//~Application();
	// override this method and put all your game inside
	virtual void game_loop();
	// if needed custom drawing put in here
	virtual void game_draw();

	// capture keyboard events
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	// Static trampoline function to the real member function callback
	static void KeyCallbackTrampoline(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	static void MouseCallbackTrampoline(GLFWwindow* window, int button, int action, int mods);
	void setWindowCallbacks(GLFWwindow* window);
	int init();
	void run();
	void poll_events();
	void update();
	void draw();
	Scene* current_scene = nullptr;
	GLFWwindow* window = nullptr;
	int width, height;
#ifdef COMPILE_IMGUI
	void handle_imgui();
	GLFWwindow* window_imgui = nullptr;
#endif
	double mouse_xpos=0, mouse_ypos=0;
	EventsManager* events_manager;
	Player* player;
	FramesController fc;
	//std::string window_name;
};

static void glfw_error_callback(int error, const char* description) {
	std::cout << "GLFW Error: " << description << std::endl;
}

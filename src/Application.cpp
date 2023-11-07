#include "Application.hpp"
#include "Font.hpp"
#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"

// TODO compiel ImGui only on debug
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>

Application::Application(int width, int height) {
	this->width = width;
	this->height = height;
}

int Application::init() {

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return -1;

	
	window_imgui = glfwCreateWindow(width, height, "Arcane2D Debug", NULL, NULL);
	window = glfwCreateWindow(width, height, "Arcane2D", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Set up the orthogonal projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	setWindowCallbacks(window);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window_imgui, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	return 0;
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key_callbacks.find(key) != key_callbacks.end())
		key_callbacks[key](window, key, scancode, action, mods);
}
// Static trampoline function to the real member function callback
void Application::KeyCallbackTrampoline(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Retrieve the instance of Application class associated with this window
	void* ptr = glfwGetWindowUserPointer(window);
	Application* app = static_cast<Application*>(ptr);

	// Call the member function key_callback
	app->key_callback(window, key, scancode, action, mods);
}

void Application::setWindowCallbacks(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, this); // Set this instance as the user pointer
	glfwSetKeyCallback(window, Application::KeyCallbackTrampoline); // Set the trampoline as the key callback
}

void Application::poll_events() {
	// Poll and handle events (inputs, window resize, etc.)
	glfwPollEvents();
}

void Application::update() {
	current_scene->update();
}

void Application::game_loop() {}

void Application::draw() {
	glfwMakeContextCurrent(window); // Make the game window's context current
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	current_scene->draw();
}

// TODO compiel ImGui only on debug
void Application::handle_imgui() {
	// Start the Dear ImGui frame
	glfwMakeContextCurrent(window_imgui); // Make the ImGui window's context current
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	// Here you can do your ImGui rendering
	ImGui::ShowDemoWindow(); // Show demo window!
	// Render ImGui
	ImGui::Render();
	glClear(GL_COLOR_BUFFER_BIT); // Clear the framebuffer
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// Swap the buffers for the ImGui window
	glfwSwapBuffers(window_imgui);
}


void Application::print_text(float x, float y, char* text, float r, float g, float b) {
	static char buffer[99999]; // ~500 chars
	int num_quads;
	unsigned char color[4] = { 0,0,0,0 };
	num_quads = stb_easy_font_print(x, y, text, color, buffer, sizeof(buffer));

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, buffer);

	glDrawArrays(GL_QUADS, 0, num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void Application::run() {
	const int max_fps = 30;
	FramesController fc(max_fps);
	// TODO debug ifdef
	const int buf_size = 128;
	char text_buffer[buf_size];
	Font font;
	font.stbtt_initfont();
	while (!glfwWindowShouldClose(window)) {
		fc.frameBegin();
		poll_events();
		update();
		game_loop();
		draw();
		// TODO debug ifdef
		sprintf_s(text_buffer, "FPS: %d\n", (int)fc.sleep_time);
		print_text(SCREEN_WIDTH/2, 10, (char*)text_buffer, 1.0f, 0.0f, 0.0f);
		font.stbtt_print(SCREEN_WIDTH / 2, 40, (char*)text_buffer);
		// Swap the buffers for the game window
		glfwSwapBuffers(window);
		handle_imgui();
		fc.frameEnd();
		fc.sleep();
		// TODO debug ifdef
		std::cout << "Fps: " << fc.sleep_time << " Real Fps: " << fc.real_fps << std::endl;
	}
	// TODO compiel ImGui only on debug
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window_imgui); // Destroy the ImGui window

	// Cleanup
	glfwDestroyWindow(window); // Destroy the game window
	glfwTerminate();
}

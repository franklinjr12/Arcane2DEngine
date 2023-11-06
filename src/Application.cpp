#include "Application.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
	// Swap the buffers for the game window
	glfwSwapBuffers(window);
}

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

void Application::run() {
	const int max_fps = 30;
	FramesController fc(max_fps);

	while (!glfwWindowShouldClose(window)) {
		fc.frameBegin();
		poll_events();
		update();
		game_loop();
		draw();
		handle_imgui();
		fc.frameEnd();
		fc.sleep();
		std::cout << "Fps: " << fc.sleep_time << " Real Fps: " << fc.real_fps << std::endl;
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window_imgui); // Destroy the ImGui window
	glfwDestroyWindow(window); // Destroy the game window
	glfwTerminate();
}

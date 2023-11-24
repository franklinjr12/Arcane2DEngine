#include "Application.hpp"

#include <stdio.h>

Application::Application(int width, int height) {
	this->width = width;
	this->height = height;
	//window_name = name;
}

//Application::~Application(){}

int Application::init() {

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return -1;

	
#ifdef COMPILE_IMGUI
	window_imgui = glfwCreateWindow(width, height, "Arcane2D Debug", NULL, NULL);
#endif
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

#ifdef COMPILE_IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window_imgui, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
#endif

	return 0;
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	EventData ed;
	ed.type = EventType::KeyboardInput;
	ed.data.push_back((event_bytes_type)EventType::KeyboardInput);
	ed.data.push_back((event_bytes_type)action);
	ed.data.push_back((event_bytes_type)key);
	events_manager->events_data.push(ed);
}

// Static trampoline function to the real member function callback
void Application::KeyCallbackTrampoline(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Retrieve the instance of Application class associated with this window
	void* ptr = glfwGetWindowUserPointer(window);
	Application* app = static_cast<Application*>(ptr);

	// Call the member function key_callback
	app->key_callback(window, key, scancode, action, mods);
}

void Application::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	EventData ed;
	ed.type = EventType::MouseInput;
	ed.data.push_back((event_bytes_type)ed.type);
	ed.data.push_back((event_bytes_type)action);
	ed.data.push_back((event_bytes_type)button);
	ed.data.push_back((event_bytes_type)mouse_xpos);
	ed.data.push_back((event_bytes_type)mouse_ypos);
	events_manager->events_data.push(ed);
}

// Static trampoline function to the real member function callback
void Application::MouseCallbackTrampoline(GLFWwindow* window, int button, int action, int mods) {
	// Retrieve the instance of Application class associated with this window
	void* ptr = glfwGetWindowUserPointer(window);
	Application* app = static_cast<Application*>(ptr);

	// Call the member function key_callback
	app->mouse_callback(window, button, action, mods);
}

void Application::setWindowCallbacks(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, this); // Set this instance as the user pointer
	glfwSetKeyCallback(window, Application::KeyCallbackTrampoline); // Set the trampoline as the key callback
	glfwSetMouseButtonCallback(window, Application::MouseCallbackTrampoline);
}

void Application::poll_events() {
	// Poll and handle events (inputs, window resize, etc.)
	glfwPollEvents();
	events_manager->run();
	glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
}

void Application::update() {
	current_scene->update();
	//player->update();
}

void Application::game_loop() {}
void Application::game_draw() {}

void Application::draw() {
	glfwMakeContextCurrent(window); // Make the game window's context current
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	current_scene->draw();
	player->draw();
}

#ifdef COMPILE_IMGUI
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
#endif

void Application::run() {
	assert(player != nullptr);
	assert(current_scene != nullptr);
	assert(events_manager != nullptr);
	const int max_fps = 30;
	FramesController fc(max_fps);
#ifdef DEBUG_SHOW_FPS
	const int buf_size = 128;
	char text_buffer[buf_size];
	Font font;
#endif
	while (!glfwWindowShouldClose(window)) {
		fc.frameBegin();
		poll_events();
		update();
		game_loop();
		draw();
		game_draw();
		// TODO debug ifdef
#ifdef DEBUG_SHOW_FPS
		sprintf_s(text_buffer, "FPS: %d\n", (int)fc.sleep_time);
		font.print(SCREEN_WIDTH / 2, 40, (char*)text_buffer);
#endif
		// Swap the buffers for the game window
		glfwSwapBuffers(window);
#ifdef COMPILE_IMGUI
		handle_imgui();
#endif
		fc.frameEnd();
		fc.sleep();
		// TODO debug ifdef
#ifdef DEBUG_SHOW_FPS
		std::cout << "Fps: " << fc.sleep_time << " Real Fps: " << fc.real_fps << std::endl;
		std::cout << "Mousex: " << mouse_xpos << " Mousey: " << mouse_ypos << "\n";
#endif
	}
#ifdef COMPILE_IMGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window_imgui); // Destroy the ImGui window
#endif

	// Cleanup
	glfwDestroyWindow(window); // Destroy the game window
	glfwTerminate();
}

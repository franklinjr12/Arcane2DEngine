#include "Application.hpp"

Application::Application(int width, int height) {
	this->width = width;
	this->height = height;
}

int Application::init() {

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return -1;

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
	return 0;
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//switch (key) {
	//case GLFW_KEY_ESCAPE:
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
	//	break;
	//case GLFW_KEY_LEFT:
	//	break;
	//case GLFW_KEY_RIGHT:
	//	current_scene->move_player(1, 0);
	//	break;
	//case GLFW_KEY_UP:
	//	break;
	//case GLFW_KEY_DOWN:
	//	break;
	//default:
	//	break;
	//}
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



void Application::run() {
	const int max_fps = 30;
	FramesController fc(max_fps);
	unsigned int counter = 0;
	while (!glfwWindowShouldClose(window))
	{
		fc.frameBegin();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		current_scene->update();

		current_scene->draw();

		glfwSwapBuffers(window);

		glfwPollEvents();
		fc.frameEnd();
		fc.sleep();
		std::cout << "Fps: " << fc.sleep_time << " Real Fps: " << fc.real_fps << std::endl;
	}

	glfwTerminate();
}

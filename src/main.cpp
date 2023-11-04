#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Image.hpp"
#include "FrameController.hpp"
#include "Body.hpp"
#include "Surface.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768



static void glfw_error_callback(int error, const char* description) {
	std::cout << "GLFW Error: " << description << std::endl;
}

int main()
{
	GLFWwindow* window;

	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Arcane2D", NULL, NULL);
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
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable 2D texturing
	glEnable(GL_TEXTURE_2D);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Image img("assets/big_demon_run_anim_f3.png");
	BodyRectangle br(0, 0, img.width, img.height);
	Body body(img, br);

	Image img2("assets/big_demon_run_anim_f3.png");
	BodyRectangle br2(SCREEN_WIDTH + 10, 0, img.width, img.height);
	Body body2(img2, br2);

	Image img3("assets/wall_edge_left.png", true);
	BodyRectangle br3(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH+30, 20);
	Body surface_body(img3, br3);
	Surface surface(surface_body);

	Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Scene scene(camera, SCREEN_WIDTH*2, SCREEN_HEIGHT*2);
	scene.bodies.push_back(body);
	scene.bodies.push_back(body2);
	scene.surfaces.push_back(surface);

	const int max_fps = 30;
	FramesController fc(max_fps);
	unsigned int counter = 0;
	while (!glfwWindowShouldClose(window))
	{
		fc.frameBegin();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		//if (isRectColliding(body.rectangle, surface.body.rectangle)) {
		//	std::cout << "Collision" << std::endl;
		//}
		//else if (counter % 3 == 0) {
		//	//body.setX(body.getX() + 5);
		//	body.setY(body.getY() + 5);
		//}

		if (counter % 3 == 0) {
			scene.camera.rect.x += 5;
		 }

		counter++;
		//body.draw();
		//body2.draw();
		//surface.draw();


		scene.draw();

		glfwSwapBuffers(window);

		glfwPollEvents();
		fc.frameEnd();
		fc.sleep();
		std::cout << "Fps: " << fc.sleep_time << " Real Fps: " << fc.real_fps << std::endl;
	}

	glfwTerminate();
	return 0;
}

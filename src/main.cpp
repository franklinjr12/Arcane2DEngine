#include <iostream>

#include "Application.hpp"

int main()
{

	Application app;
	app.init();

	Image img("assets/main_character.png");
	BodyRectangle br(0, 0, img.width, img.height);
	Body body(img, br);

	Image img2("assets/big_demon_run_anim_f3.png");
	BodyRectangle br2(SCREEN_WIDTH + 10, 0, img.width, img.height);
	Body body2(img2, br2);

	Image img3("assets/wall_edge_left.png", true);
	BodyRectangle br3(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH + 30, 20);
	Body surface_body(img3, br3);
	Surface surface(surface_body);

	Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Scene scene(camera, body, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	scene.gravity = 0;
	scene.bodies.push_back(&body);
	scene.bodies.push_back(&body2);
	scene.surfaces.push_back(&surface);

	app.current_scene = &scene;
	app.key_callbacks[GLFW_KEY_LEFT] = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		((Application*)glfwGetWindowUserPointer(window))->current_scene->move_player(-1, 0);
	};
	app.key_callbacks[GLFW_KEY_RIGHT] = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		((Application*)glfwGetWindowUserPointer(window))->current_scene->move_player(1, 0);
	};
	app.key_callbacks[GLFW_KEY_UP] = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		((Application*)glfwGetWindowUserPointer(window))->current_scene->move_player(0, -1);
	};
	app.key_callbacks[GLFW_KEY_DOWN] = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		((Application*)glfwGetWindowUserPointer(window))->current_scene->move_player(0, 1);
	};

	int neww = 200, newh = 200;
	//Image btn_img("assets/basic_button.png");
	Image btn_img("assets/basic_button.png", neww, newh);
	//btn_img.resize(neww, newh);
	Button btn((SCREEN_WIDTH - SCREEN_WIDTH / 3), 10, neww, newh, "btn", btn_img);
	app.current_scene->buttons.push_back(&btn);


	app.run();

	return 0;
}

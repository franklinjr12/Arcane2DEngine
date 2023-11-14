#include <iostream>

#include "Application.hpp"

class GameExample : public Application {
public:
	GameExample() {

	}
	void game_loop() override {

	}
	void game_draw() override {

	}
};

int main()
{

	GameExample app;
	app.init();

	Image img("assets/main_character.png");
	Image ske1("assets/skelleton1.png");
	Image ske2("assets/skelleton2.png");
	Image ske3("assets/skelleton3.png");
	Image ske4("assets/skelleton4.png");
	img = ske1;
	BodyRectangle br(0, 0, img.width, img.height);
	Body body(img, br);
	Player player(body);
	player.handler.callback = [&player](std::vector<event_bytes_type> data) {
		player.process_events(data);
		};
	player.animation.add_animation(ske1);
	player.animation.add_animation(ske2);
	player.animation.add_animation(ske3);
	player.animation.add_animation(ske4);

	Image img2("assets/big_demon_run_anim_f3.png");
	BodyRectangle br2(SCREEN_WIDTH + 10, 0, img.width, img.height);
	Body body2(img2, br2);

	Image img3("assets/wall_edge_left.png", true);
	BodyRectangle br3(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH + 30, 20);
	Body surface_body(img3, br3);
	Surface surface(surface_body);

	Camera camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Image background("assets/dark_cloud_background1024_720.png");
	Scene scene(camera, body, background, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	scene.gravity = 0;
	//scene.bodies.push_back(&body);
	scene.bodies.push_back(&body2);
	scene.surfaces.push_back(&surface);

	app.current_scene = &scene;
	app.player = &player;

	int neww = 200, newh = 200;
	Image btn_img("assets/basic_button.png", neww, newh);
	Button btn((SCREEN_WIDTH - SCREEN_WIDTH / 3), 10, neww, newh, "btn", btn_img);
	app.current_scene->buttons.push_back(&btn);

	EventsManager ev_manager;
	ev_manager.subscribe(EventType::KeyboardInput, player.handler);
	app.events_manager = &ev_manager;

	app.run();

	return 0;
}

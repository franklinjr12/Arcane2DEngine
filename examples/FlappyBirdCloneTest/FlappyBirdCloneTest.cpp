#include <ArcaneVersion.hpp>
#include <Application.hpp>

#include <iostream>
#include <chrono>

using namespace std::chrono;

const std::string bird_name = "bird";
const std::string tunnel_name = "tunnel";

class Bird : public Player {
public:

	Bird() {
		image = new Image("assets/bird.png");
		Vecf initial_pos = { 60 + image->width, SCREEN_HEIGHT / 2 };
		rectangle = new BodyRectangle(initial_pos, image->width, image->height);
		name = bird_name;
		setX(initial_pos[0]);
		setY(initial_pos[1]);
		suffer_gravity = true;
	}

	void _update() override {
		if (vel[1] > 5)
			vel[1] = 5;
		else if (vel[1] < -5)
			vel[1] = -5;
	}

	const float vel_up = -10;
};

class Tunnel : public DynamicBody {
public:

	Tunnel(bool top = false, int height = 186) {
		const int default_width = 57;
		if (top)
			image = new Image("assets/fbird_tunnel.png", default_width, height, false, false);
		else
			image = new Image("assets/fbird_tunnel.png", default_width, height);
		Vecf initial_pos = { SCREEN_WIDTH, SCREEN_HEIGHT - image->height };
		if (top)
			initial_pos[1] = 0;
		rectangle = new BodyRectangle(initial_pos, image->width, image->height);
		name = tunnel_name;
		setX(initial_pos[0]);
		setY(initial_pos[1]);
		suffer_gravity = false;
		vel[0] = xvel;
	}

	const float xvel = -5;
};

class FlappyBird : public Application {
public:

	void game_loop() override {
		
	}

	void game_draw() override {
	}

	bool last_tunnel_top = false;
	system_clock::time_point tp;

};

static FlappyBird* app;

int main()
{
	printf("Flappy Bird app!\n");
	printf("Arcane version: %s\n", arcane_version_string().c_str());

	app = new FlappyBird();
	app->init();

	Bird* player = new Bird();
	app->player = player;
	player->handler.callback = [player](std::vector<event_bytes_type> data) {
		switch (data[0]) {
		case (event_bytes_type)EventType::KeyboardInput:
			if (data[1] == GLFW_PRESS || data[1] == GLFW_REPEAT) {
				switch (data[2]) {
				case GLFW_KEY_SPACE:
					player->vel[1] += player->vel_up;
					break;
				default:
					break;
				}
			}
		}
		};

	Camera* camera = new Camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Scene* scene = new Scene(camera, nullptr, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	scene->gravity = 1;

	Tunnel* t1 = new Tunnel(true, 600);

	scene->add_body(player);
	scene->add_body(t1);

	EventsManager ev_manager;
	ev_manager.subscribe(EventType::KeyboardInput, player->handler);

	app->events_manager = &ev_manager;
	app->current_scene = scene;

	app->run();

	delete app;

}

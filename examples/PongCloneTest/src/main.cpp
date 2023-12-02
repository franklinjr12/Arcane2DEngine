#include <ArcaneVersion.hpp>
#include <Application.hpp>
#include <cstdio>

class Pong : public Application {
public:

	void game_loop() override {

	}

	void game_draw() override {

	}
};

static Pong* app;

class Paddle : public DynamicBody {
public:

	Paddle(Veci initial_pos) {
		const std::string sprite_path = "assets/paddle.png";
		image = new Image(sprite_path);
		rectangle = new BodyRectangle(pos.pos, image->width, image->height);
		setX(initial_pos[0]);
		setY(initial_pos[1]);
	}

	const float paddle_vel = 5;
};

class PlayerPaddle : public Player {
public:

	PlayerPaddle() {
		Veci initial_pos = { 1, SCREEN_HEIGHT / 2 };
		paddle = new Paddle(initial_pos);
		image = paddle->image;
		rectangle = paddle->rectangle;
		setX(paddle->getX());
		setY(paddle->getY());
	}

	Paddle* paddle;
};

class Ball : public DynamicBody {
public:

	Ball() {
		const std::string sprite_path = "assets/ball10x10.png";
		image = new Image(sprite_path);
		rectangle = new BodyRectangle(pos.pos, image->width, image->height);
		setX(SCREEN_WIDTH / 2);
		setY(SCREEN_HEIGHT / 2);
		vel[0] = -ball_vel;
		vel[1] = -ball_vel;
	}

	const float ball_vel = 10;
};

int main() {

	printf("Pong app!\n");
	printf("Arcane version: %s\n", arcane_version_string().c_str());

	app = new Pong();
	app->init();

	PlayerPaddle* player = new PlayerPaddle();
	player->handler.callback = [player](std::vector<event_bytes_type> data) {
		switch (data[0]) {
		case (event_bytes_type)EventType::KeyboardInput:
			if (data[1] == GLFW_PRESS || data[1] == GLFW_REPEAT) {
				switch (data[2]) {
				case GLFW_KEY_UP:
					player->vel[1] = -player->paddle->paddle_vel;
					break;
				case GLFW_KEY_DOWN:
					player->vel[1] = player->paddle->paddle_vel;
					break;
				default:
					break;
				}
			}
			if (data[1] == GLFW_RELEASE) {
				switch (data[2]) {
				case GLFW_KEY_UP:
				case GLFW_KEY_DOWN:
					player->vel[1] = 0;
					break;
				default:
					break;
				}
			}
		}
		};

	Ball* ball = new Ball();

	Camera* camera = new Camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Scene* scene = new Scene(camera, nullptr, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	scene->gravity = 0;

	scene->add_body(player);
	scene->add_body(ball);

	EventsManager ev_manager;
	ev_manager.subscribe(EventType::KeyboardInput, player->handler);

	app->events_manager = &ev_manager;
	app->current_scene = scene;
	app->player = player;

	app->run();

	delete app;

	return 0;
}
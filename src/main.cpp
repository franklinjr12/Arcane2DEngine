#include "Application.hpp"
#include "DynamicBody.hpp"

#include <iostream>
#include <Windows.h>

class GameExample : public Application {
public:
	GameExample() {

	}
	void game_loop() override {

	}
	void game_draw() override {
		const int buf_size = 128;
		char text_buffer[buf_size];
		Font font;
		sprintf_s(text_buffer, "mx: %03d my: %03d", (int)mouse_pos[0], (int)mouse_pos[1]);
		font.print(10, 40, (char*)text_buffer);
		sprintf_s(text_buffer, "px: %03d py: %03d", (int)player->getX(), (int)player->getY());
		font.print(10, 60, (char*)text_buffer);
		sprintf_s(text_buffer, "rx: %03d ry: %03d", (int)player->rectangle->pos.x, (int)player->rectangle->pos.x);
		font.print(10, 80, (char*)text_buffer);
#ifdef DEBUG_SHOW_FPS
		sprintf_s(text_buffer, "FPS: %d\n", (int)fc.sleep_time);
		font.print(SCREEN_WIDTH / 2, 100, (char*)text_buffer);
#endif
	}
};

class MovablePlayer : public Player {
public:

	MovablePlayer() {
		image = new Image("assets/main_character.png");
		Vecf p1 = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 };
		rectangle = new BodyRectangle(p1, image->width, image->height);
		setX(p1[0]);
		setY(p1[1]);
	}

	void process_events(std::vector<event_bytes_type> data) override {
		switch (data[0]) {
		case (event_bytes_type)EventType::KeyboardInput:
			if (data[1] == GLFW_PRESS || GLFW_RELEASE) {
				switch (data[2]) {
				case GLFW_KEY_RIGHT:
					vel[0] = 5;
					break;
				case GLFW_KEY_LEFT:
					vel[0] = -5;
					break;

				case GLFW_KEY_DOWN:
					vel[1] = 5;
					break;

				case GLFW_KEY_UP:
					vel[1] = -5;
					break;
				default:
					break;
				}
			}
			else {
				vel[0] = 0;
				vel[1] = 0;
			}
			break;
		default:
			break;
		}
	}
};

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
	GameExample* app = new GameExample();
	app->init();

	//Image ske1("assets/skelleton1.png");
	//Image ske2("assets/skelleton2.png");
	//Image ske3("assets/skelleton3.png");
	//Image ske4("assets/skelleton4.png");
	//img = ske1;
	MovablePlayer* player = new MovablePlayer();
	player->draw_rect_overlay = true;
	player->vel[0] = 0.1;
	//player->animation.add_animation(ske1);
	//player->animation.add_animation(ske2);
	//player->animation.add_animation(ske3);
	//player->animation.add_animation(ske4);

	//Image img2("assets/big_demon_run_anim_f3.png");
	//BodyRectangle br2(SCREEN_WIDTH + 10, 0, img.width, img.height);
	//Body body2(img2, br2);

	//Image img3("assets/wall_edge_left.png", true);
	//BodyRectangle br3(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH + 30, 20);
	//Body surface_body(img3, br3);
	//Surface surface(surface_body);

	//Image particle_img("assets/first_spell.png", 100, 100);
	//Image particle_img("assets/first_spell.png");
	//BodyRectangle particle_rect(0, 300, particle_img.width, particle_img.height);
	//Body particle_body(particle_img, particle_rect);
	//particle_body.suffer_gravity = false;
	//particle_body.vel_y = 5;
	//Particle particle1(particle_body);

	//Image particle_img2("assets/first_spell.png");
	//BodyRectangle particle_rect2(0, 300, particle_img2.width, particle_img2.height);
	//Body particle_body2(particle_img2, particle_rect2);
	//particle_body2.suffer_gravity = false;
	//particle_body2.vel_x = 5;
	//particle_body2.vel_y = 5;
	//Particle particle2(particle_body2);

	Camera* camera = new Camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Image* background = new Image("assets/dark_cloud_background1024_720.png");
	Scene* scene = new Scene(camera, background, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	scene->gravity = 0;
	//scene.bodies.push_back(&body);
	//scene.bodies.push_back(&body2);
	//scene.surfaces.push_back(&surface);
	//scene.particles.push_back(&particle1);
	//scene.particles.push_back(&particle2);

	Image* img2 = new Image("assets/main_character.png");
	Vecf p2 = { SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 };
	BodyRectangle* br2 = new BodyRectangle(p2, img2->width, img2->height);
	DynamicBody* b2 = new DynamicBody(img2, br2);
	b2->draw_rect_overlay = true;
	b2->vel[0] = -1;

	//scene.bodies.push_front(&player);
	//scene.bodies.push_front(&b2);
	scene->add_body(player);
	scene->add_body(b2);

	app->current_scene = scene;
	app->player = player;

	int neww = 200, newh = 200;
	Image btn_img("assets/basic_button.png", neww, newh);
	Vecf button_pos = { (SCREEN_WIDTH - SCREEN_WIDTH / 3), 10 };
	Button btn(button_pos, &btn_img, neww, newh, "btn");
	//Button btn((SCREEN_WIDTH - SCREEN_WIDTH / 3), 10, neww, newh, "btn", btn_img);
	//app->current_scene->buttons.push_back(&btn);
	scene->uis.push_front(&btn);

	app->events_manager = EventsManager::getInstance();
	app->events_manager->subscribe(EventType::KeyboardInput, player);

	app->run();

	delete app;

	return 0;
}

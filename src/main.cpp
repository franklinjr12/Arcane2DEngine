#include "Application.hpp"
#include "DynamicBody.hpp"
#include "ProgressBar.hpp"
#include "TextDisplay.hpp"
#include "ImageDisplay.hpp"
#include "FontsManager.hpp"

#include <iostream>
#include <Windows.h>

class GameExample : public Application {
public:

	GameExample() {
		start_btn = nullptr;
	}
	void game_loop() override {
	}
	void game_draw() override {
		Vecf pos;
		pos[0] = 10;
		pos[1] = 40;
		const int buf_size = 128;
		char text_buffer[buf_size];
		sprintf_s(text_buffer, "mx: %03d my: %03d", (int)mouse_pos[0], (int)mouse_pos[1]);
		font->print(pos, (char*)text_buffer);
		pos[1] += 20;
		sprintf_s(text_buffer, "px: %03d py: %03d", (int)player->getX(), (int)player->getY());
		font->print(pos, (char*)text_buffer);
		pos[1] += 20;
		sprintf_s(text_buffer, "rx: %03d ry: %03d", (int)player->rectangle->pos.x, (int)player->rectangle->pos.x);
		font->print(pos, (char*)text_buffer);
#ifdef DEBUG_SHOW_FPS
		pos[0] = DEFAULT_SCREEN_WIDTH / 2;
		pos[1] = 100;
		sprintf_s(text_buffer, "FPS: %d\n", (int)fc.sleep_time);
		font->print(pos, (char*)text_buffer);
		//delete font;
#endif
	}
	void process_events(std::vector<event_bytes_type> data) override {
		switch (data[0]) {
		case (event_bytes_type)EventType::ButtonClicked:
			ObjectId btn_id = (ObjectId)data[1];
			if (start_btn != nullptr && btn_id == start_btn->id) {
				if (game_scene != nullptr) {
					current_scene = game_scene;
					font = font_small;
				}
			}
		}
	}

	Font* font;
	Font* font_small;
	Font* font_big;
	Button* start_btn;
	Scene* menu_scene;
	Scene* game_scene;
};

class MyPlayer : public Player {
public:

	MyPlayer() {
		image = new Image("assets/main_character.png");
		Vecf p1 = { DEFAULT_SCREEN_WIDTH / 2 , DEFAULT_SCREEN_HEIGHT / 2 };
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
		case (event_bytes_type)EventType::ButtonClicked:
			A2D_LOGI("got button event!");
			health_ui->set_current(health_ui->current - 10);
			break;
		default:
			break;
		}
	}

	ProgressBar* health_ui;
};

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
	GameExample* app = new GameExample();
	app->init();

	// can only initialize fonts after app->init()
	std::string font_path = "assets/16020_FUTURAM.ttf";
	int font_size = 16;
	app->font_small = new Font(font_path, font_size);
	font_size = 64;
	app->font_big = new Font(font_path, font_size);
	app->font = app->font_big;


	//Image ske1("assets/skelleton1.png");
	//Image ske2("assets/skelleton2.png");
	//Image ske3("assets/skelleton3.png");
	//Image ske4("assets/skelleton4.png");
	//img = ske1;
	MyPlayer* player = new MyPlayer();
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
	//BodyRectangle br3(0, DEFAULT_SCREEN_HEIGHT / 2, SCREEN_WIDTH + 30, 20);
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

	Camera* camera = new Camera(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	Image* background = new Image("assets/dark_cloud_background1024_720.png");
	Scene* scene = new Scene(camera, background, DEFAULT_SCREEN_WIDTH * 2, DEFAULT_SCREEN_HEIGHT * 2);
	scene->gravity = 0;
	//scene.bodies.push_back(&body);
	//scene.bodies.push_back(&body2);
	//scene.surfaces.push_back(&surface);
	//scene.particles.push_back(&particle1);
	//scene.particles.push_back(&particle2);

	Image* img2 = new Image("assets/main_character.png");
	Vecf p2 = { DEFAULT_SCREEN_WIDTH / 2 + 100, DEFAULT_SCREEN_HEIGHT / 2 };
	BodyRectangle* br2 = new BodyRectangle(p2, img2->width, img2->height);
	DynamicBody* b2 = new DynamicBody(img2, br2);
	b2->draw_rect_overlay = true;
	b2->vel[0] = -1;

	//scene.bodies.push_front(&player);
	//scene.bodies.push_front(&b2);
	player->name = "player name";
	b2->name = "b2 name";
	scene->add_body(player);
	scene->add_body(b2);

	app->game_scene = scene;
	app->player = player;

	// Ui components

	// button
	int neww = 200, newh = 200;
	//Image btn_img("assets/basic_button.png", neww, newh);
	Image btn_img("assets/basic_button_text.png", neww, newh);
	Vecf button_pos = { (DEFAULT_SCREEN_WIDTH - DEFAULT_SCREEN_WIDTH / 3), 10 };
	Button btn(button_pos, &btn_img, neww, newh);

	// progress bar
	Image* progress_back = new Image("assets/progress_bar.png");
	Image* progress_front = new Image("assets/progress_bar_front.png");
	Vecf pb_pos;
	pb_pos[0] = 10;
	pb_pos[1] = DEFAULT_SCREEN_HEIGHT - 60;
	ProgressBar* pb = new ProgressBar(pb_pos, progress_back, progress_front);
	//pb->set_current(50);
	player->health_ui = pb;

	// text display
	Image* text_display_image = new Image("assets/basic_button.png");
	Vecf text_pos = { DEFAULT_SCREEN_WIDTH / 2, DEFAULT_SCREEN_HEIGHT - 60 };
	Font* f = FontsManager::get_instance()->default_font;
	std::string t = "T";
	TextDisplay* td = new TextDisplay(text_pos, text_display_image, t, new Font(*f));
	td->font_pos[0] = td->pos[0] + 5;
	td->font_pos[1] = td->pos[1] + td->image->height / 2 + 5;

	// add Ui to scene
	btn.name = "button name";
	pb->name = "progressbar name";
	td->name = "textdisplay name";
	scene->uis.push_front(&btn);
	scene->uis.push_front(pb);
	scene->uis.push_front(td);
	scene->name = "main scene";
	scene->groups.push_back((ObjectGroup)22);
	scene->groups.push_back((ObjectGroup)100);
	scene->gravity = 0.98;

	// Menu scene
	Scene* menu_scene = new Scene(new Camera(*camera), new Image(*background), DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

	//start button
	int start_btn_w = 200, start_btn_h = 200;
	Image btn_start_img("assets/basic_button.png", start_btn_w, start_btn_h);
	Vecf button_start_pos = { DEFAULT_SCREEN_WIDTH / 2 - btn_start_img.width / 2, DEFAULT_SCREEN_HEIGHT / 2 - btn_start_img.height / 2 };
	Font* font_start = FontsManager::get_instance()->default_font;
	Button* btn_start = new Button(button_start_pos, &btn_start_img, start_btn_w, start_btn_h, "START", font_start);
	btn_start->font_pos[0] = btn_start->pos[0] + 20;
	btn_start->font_pos[1] = btn_start->pos[1] + 60;

	menu_scene->uis.push_front(btn_start);
	app->start_btn = btn_start;

	app->menu_scene = menu_scene;
	app->current_scene = menu_scene;

	// events
	app->events_manager = EventsManager::getInstance();
	app->events_manager->subscribe(EventType::KeyboardInput, player);
	app->events_manager->subscribe(EventType::ButtonClicked, player);
	app->events_manager->subscribe(EventType::MouseInput, scene);
	app->events_manager->subscribe(EventType::MouseInput, menu_scene);
	app->events_manager->subscribe(EventType::ButtonClicked, app);

	scene->save_scene_to_file("scene.txt");

	scene->load_scene_from_file("scene.txt");

	// infinity loop
	app->run();

	// cleanup
	delete app;

	return 0;
}

#include "Scene.hpp"

#include "ArcaneUtils.hpp"
#include "Collisions.hpp"
#include "Logger.hpp"
#include "StaticBody.hpp"
#include "Button.hpp"
#include "ProgressBar.hpp"
#include "ImageDisplay.hpp"
#include "TextDisplay.hpp"

Scene::Scene(Camera* camera, Image* background, uint32_t w, uint32_t h) : camera(camera), background(background), w(w), h(h) {}

void Scene::update(Veci mouse_pos) {
	for (auto it = bodies.begin(); it != bodies.end(); it++) {
		Body* body = *it;
		if (body->suffer_gravity)
			body->update(gravity);
		else
			body->update();
		// TODO check if there is a better way to check collisions
		if (body->can_collide) {
			for (auto it_inner = bodies.begin(); it_inner != bodies.end(); it_inner++) {
				Body* body_inner = *it_inner;
				if (body_inner->can_collide) {
					if (isRectColliding(*body->rectangle, *body_inner->rectangle)) {
						if (body != body_inner) { // don't check collision with self
							body->collided = true;
							body_inner->collided = true;
							body->handle_collision(body_inner->id);
						}
					}
				}
			}
		}
	}
	for (auto it = uis.begin(); it != uis.end(); it++) {
		UiComponent* ui = *it;
		if (ui->should_draw) {
			Point p;
			p.x = mouse_pos[0];
			p.y = mouse_pos[1];
			if (isPointRectColliding(*(ui->rect), p))
				ui->mouse_over();
		}
	}
}

void Scene::process_events(std::vector<event_bytes_type> data) {
	switch (data[0]) {
	case (event_bytes_type)EventType::MouseInput:
		if (data[1] == GLFW_PRESS && data[2] == GLFW_MOUSE_BUTTON_1) {
			for (auto it = uis.begin(); it != uis.end(); it++) {
				UiComponent* ui = *it;
				if (ui->should_draw) {
					Point p;
					p.x = data[3];
					p.y = data[4];
					if (isPointRectColliding(*(ui->rect), p))
						ui->on_click();
				}
			}
		}
		break;
	default:
		;
	}
}

void Scene::draw() {
	if (background)
		background->draw(Vecf{ camera->rect.pos.x, camera->rect.pos.y }, background->width, background->height);
	for (auto it = bodies.begin(); it != bodies.end(); it++) {
		Body* body = *it;
		if (isRectColliding(*body->rectangle, camera->rect)) {
			Point p;
			p.x = body->getX();
			p.y = body->getY();
			body->setX(p.x + camera->rect.pos.x);
			body->setY(p.y + camera->rect.pos.y);
			body->draw();
			body->setX(p.x);
			body->setY(p.y);
		}
	}
	for (auto it = uis.begin(); it != uis.end(); it++) {
		UiComponent* ui = *it;
		if (ui->should_draw) {
			Point p;
			p.x = ui->pos[0];
			p.y = ui->pos[1];
			ui->pos[0] = p.x + camera->rect.pos.x;
			ui->pos[1] = p.y + camera->rect.pos.y;
			ui->draw();
			ui->pos[0] = p.x;
			ui->pos[1] = p.y;
		}
	}
}

void Scene::resolution_changed(int new_width, int new_height) {
	//float width_ratio = ((float)new_width) / DEFAULT_SCREEN_WIDTH;
	//float height_ratio = ((float)new_height) / DEFAULT_SCREEN_HEIGHT;
	//if (background)
	//	background->resize(background->width * width_ratio, background->height * height_ratio);
	//camera->rect.w = camera->rect.w * width_ratio;
	//camera->rect.h = camera->rect.h * height_ratio;
	//for (auto it = bodies.begin(); it != bodies.end(); it++) {
	//	Body* body = *it;
	//	int w = body->rectangle->w * width_ratio;
	//	int h = body->rectangle->h * height_ratio;
	//	if(w > 0 && h > 0)
	//		body->resize(w, h);
	//}
	//for (auto it = uis.begin(); it != uis.end(); it++) {
	//	UiComponent* ui = *it;
	//	int w = ui->rect->w * width_ratio;
	//	int h = ui->rect->h * height_ratio;
	//	if (w > 0 && h > 0)
	//		ui->resize(ui->rect->w * width_ratio, ui->rect->h * height_ratio);
	//}
}

void Scene::add_body(Body* body) {
	A2D_LOGI("body {} added", body->id);
	bodies.push_front(body);
	bodies_map[body->id] = body;
}

Body* Scene::get_body(ObjectId id) {
	return bodies_map[id];
}

Body* Scene::remove_body(ObjectId id) {
	A2D_LOGI("body {} removed", id);
	auto prev = bodies.before_begin();
	auto current = bodies.begin();

	while (current != bodies.end()) {
		if ((*current)->id == id) {
			// Body with the specified ID found

			// Remove the body from the 'bodies' container
			current = bodies.erase_after(prev);

			// Remove the body from the 'bodies_map' container
			auto it = bodies_map.find(id);
			if (it != bodies_map.end()) {
				bodies_map.erase(it);
			}

			if (current == bodies.end()) return nullptr;
			return *current; // Return a pointer to the removed body
		}

		++prev;
		++current;
	}

	// Body with the specified ID not found
	return nullptr;
}

Scene::Scene(std::vector<char>& serialized_data) {
	size_t bytes_size;
	const char* ptr;
	ObjectType ot;
	
	w = *reinterpret_cast<const uint32_t*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(w));
	h = *reinterpret_cast<const uint32_t*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(h));
	gravity = *reinterpret_cast<const float*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(gravity));

	bytes_size = *reinterpret_cast<const size_t*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(bytes_size));
	auto v = std::vector<char>(serialized_data.begin(), serialized_data.begin() + bytes_size);
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size);
	camera = new Camera(v);

	bytes_size = *reinterpret_cast<const size_t*>(serialized_data.data());
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(bytes_size));
	v = std::vector<char>(serialized_data.begin(), serialized_data.begin() + bytes_size);
	serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size);
	background = new Image(v);

	while (!serialized_data.empty()) {
		ot = *reinterpret_cast<const ObjectType*>(serialized_data.data());
		serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(ot));
		bytes_size = *reinterpret_cast<const size_t*>(serialized_data.data());
		serialized_data.erase(serialized_data.begin(), serialized_data.begin() + sizeof(bytes_size));
		v = std::vector<char>(serialized_data.begin(), serialized_data.begin() + bytes_size);
		serialized_data.erase(serialized_data.begin(), serialized_data.begin() + bytes_size);
		// check if it is really needed to case for types like Object, Image...
		switch (ot) {
		case ObjectType::Body:
		{
			Body* b = new Body(v);
			add_body(b);
			break;
		}
		case ObjectType::DynamicBody:
		{
			auto* d = new DynamicBody(v);
			add_body(d);
			break;
		}
		case ObjectType::StaticBody:
		{
			auto* s = new StaticBody(v);
			add_body(s);
			break;
		}
		case ObjectType::UiComponent:
		{
			auto* u = new UiComponent(v);
			uis.push_front(u);
			break;
		}
		case ObjectType::Button:
		{
			auto* bu = new Button(v);
			uis.push_front(bu);
			break;
		}
		case ObjectType::ProgressBar:
		{
			auto* pu = new ProgressBar(v);
			uis.push_front(pu);
			break;
		}
		case ObjectType::TextDisplay:
		{
			auto* tu = new TextDisplay(v);
			uis.push_front(tu);
			break;
		}
		case ObjectType::ImageDisplay:
		{
			auto* iu = new ImageDisplay(v);
			uis.push_front(iu);
			break;
		}
		}
	}
}

std::vector<char> Scene::serialize() {
	std::vector<char> v;
	size_t bytes_size;
	const char* ptr;
	ObjectType ot;

	ptr = reinterpret_cast<const char*>(&w);
	v.insert(v.end(), ptr, ptr + sizeof(w));
	ptr = reinterpret_cast<const char*>(&h);
	v.insert(v.end(), ptr, ptr + sizeof(h));
	ptr = reinterpret_cast<const char*>(&gravity);
	v.insert(v.end(), ptr, ptr + sizeof(gravity));

	auto ser_camera = camera->serialize();
	bytes_size = ser_camera.size();
	ptr = reinterpret_cast<const char*>(&bytes_size);
	v.insert(v.end(), ptr, ptr + sizeof(bytes_size));
	v.insert(v.end(), ser_camera.begin(), ser_camera.end());

	auto ser_back = background->serialize();
	bytes_size = ser_back.size();
	ptr = reinterpret_cast<const char*>(&bytes_size);
	v.insert(v.end(), ptr, ptr + sizeof(bytes_size));
	v.insert(v.end(), ser_back.begin(), ser_back.end());

	for (Object* e : bodies) {
		ot = e->get_type();
		ptr = reinterpret_cast<const char*>(&ot);
		v.insert(v.end(), ptr, ptr + sizeof(ot));
		auto ser = e->serialize();
		bytes_size = ser.size();
		ptr = reinterpret_cast<const char*>(&bytes_size);
		v.insert(v.end(), ptr, ptr + sizeof(bytes_size));
		v.insert(v.end(), ser.begin(), ser.end());
	}

	for (Object* e : uis) {
		ot = e->get_type();
		ptr = reinterpret_cast<const char*>(&ot);
		v.insert(v.end(), ptr, ptr + sizeof(ot));
		auto ser = e->serialize();
		bytes_size = ser.size();
		ptr = reinterpret_cast<const char*>(&bytes_size);
		v.insert(v.end(), ptr, ptr + sizeof(bytes_size));
		v.insert(v.end(), ser.begin(), ser.end());
	}

	return v;
}

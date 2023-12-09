#include "ProgressBar.hpp"

ProgressBar::ProgressBar(Vecf pos, Image* back, Image* front, int min, int max) {
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	progress_back = back;
	progress_front = front;
	original_width = front->width;
	this->min = min;
	this->max = max;
	current = max;
	last_current = current;
	rect = new BodyRectangle(pos, back->width, back->height);
}

void ProgressBar::draw() {
	if (should_draw) {
		progress_back->draw(pos, progress_back->width, progress_front->height);
		if (current < 1) current = 1;
		if (last_current != current) {
			last_current = current;
			progress_front->resize((current * original_width) / max, progress_front->height);
		}
		progress_front->draw(pos, current, progress_front->height);
	}
}

void ProgressBar::set_max(int nmax) {
	max = nmax;
}

void ProgressBar::set_current(int ncurrent) {
	current = ncurrent;
}

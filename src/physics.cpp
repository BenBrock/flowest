#include <stdio.h>
#include <unistd.h> // for usleep()
#include "physics.hpp"


#define DELTA_T 1.0


WindTunnel::WindTunnel() {
	field = new FieldF(w, h);
	t = 0.0;
	running = false;
}

WindTunnel::~WindTunnel() {
	delete field;
}

void WindTunnel::start() {
	// Initial conditions
	field->clear();
	
	// Timestepping
	for (running = true; running; t += DELTA_T) {
		step();
		usleep(10000);
	}
}

void WindTunnel::stop() {
	running = false;
}

void WindTunnel::step() {
	std::lock_guard<std::recursive_mutex> lock(stepMutex);
	
	FieldF *newField = new FieldF(w, h);
	
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			newField->at(x, y) = field->at(x, y) + (float) rand() / RAND_MAX;
		}
	}
	
	delete field;
	field = newField;
}


WindTunnelElement::WindTunnelElement() {
	windTunnel = new WindTunnel();
}

void WindTunnelElement::start() {
	windTunnel->start();
}

void WindTunnelElement::stop() {
	windTunnel->stop();
}

void WindTunnelElement::paint(int width, int height, Pixel *pixels) {
	std::lock_guard<std::recursive_mutex> lock(windTunnel->stepMutex);
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float value = windTunnel->field->at(x, y);
			pixels[x + width * y].setRGBA(0, 0, value);
		}
	}
}

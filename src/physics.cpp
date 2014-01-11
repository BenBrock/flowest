#include <stdio.h>
#include <unistd.h> // for usleep()
#include "physics.hpp"


#define DELTA_T 1.0


WindTunnel::WindTunnel() {
	U = new FieldF(w, h);
	t = 0.0;
	running = false;
}

WindTunnel::~WindTunnel() {
	delete U;
}

void WindTunnel::start() {
	// Initial conditions
	U->clear(0.0);
	
	for (int i = 0; i < 10; i++) {
		U->at(rand() % w, rand() % h) = 2.0;
	}
	
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
	
	// static float alpha = 0.1;
	// FieldF *new_U = new FieldF(w, h);
	
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// float u = U->at(x, y);
			// float lapl_u = U->laplacian(x, y);
			// new_U->at(x, y) = u + DELTA_T * alpha * lapl_u;
			
			// Cellular Automata
			// rule 30
			float &u = U->at(x, y);
			if (u <= 0.0) {
				int pattern = 0;
				if (U->atSafe(x - 1, y - 1) > 0.0)
					pattern |= 1;
				if (U->atSafe(x, y - 1) > 0.0)
					pattern |= 2;
				if (U->atSafe(x + 1, y - 1) > 0.0)
					pattern |= 4;
				
				static bool rule[] = {0, 1, 1, 1, 1, 0, 0, 0};
				if (rule[pattern]) {
					u = 1.0;
				}
			}
			else {
				u -= 1.0/32;
			}
		}
	}
	
	// delete U;
	// U = new_U;
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
			float value = windTunnel->U->at(x, y);
			pixels[x + width * y].setRGBA(0, 0, clip(0, 255, value * 256));
		}
	}
}

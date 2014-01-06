#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <thread>
#include <SDL2/SDL.h>
#include "flowest.hpp"
#include "graphics.hpp"
#include "Surface.h"


void check(bool success, const char *errFormat, ...) {
	va_list vl;
	va_start(vl, errFormat);
	
	if (!success) {
		if (errFormat) {
			vfprintf(stderr, errFormat, vl);
			fprintf(stderr, "\n");
		}
		abort();
	}
	va_end(vl);
}

/** Serves as boilerplate code for creating draw*() functions
*/
void drawColorWheel(Display *display) {
	for (int b = 0; display->running; b = (b + 1) % 256) {
		SDL_Surface *dest = display->createNextSurface();
		SDL_LockSurface(dest);
		
		Uint32 *pixels = (Uint32 *) dest->pixels;
		for (int y = 0; y < dest->h; y++) {
			for (int x = 0; x < dest->w; x++) {
				pixels[x + dest->w * y] = SDL_MapRGB(dest->format, 255-x, x, b);
			}
		}
		
		SDL_UnlockSurface(dest);
		display->setNextSurface(dest);
		SDL_Delay(10);
	}
}

/*
void drawShadow(Display &display, Surface *surface) {
	TextureLocker tl(display);
	
	for (Voxel *voxel : surface->voxels) {
		// Project the voxel onto the X-Y plane, centered at (0, 0)
		int srcX = voxel->position.x + tl.width / 2;
		int srcY = voxel->position.z + tl.height / 2;
		
		tl.at(srcX, srcY).setRGBA(255, 255, 255);
	}
}

void testSurface(Display &display) {
	// Create surface and mutate it a few times
	Surface *surface = new Surface(64);
	for (int i = 0; i < 100; i++) {
		surface->mutate();
	}
	
	drawShadow(display, surface);
	
	delete surface;
}
*/

int main(int argc, const char **argv) {
	SDL_Init(SDL_INIT_VIDEO);
	srand(time(NULL));
	
	// Create display
	Display display(256, 256, 2);
	std::thread drawThread(drawColorWheel, &display);
	display.start();
	drawThread.join();
	
	// Cleanup
	SDL_Quit();
	
	// It's pretty unlikely that this will return 1
	return !rand();
}
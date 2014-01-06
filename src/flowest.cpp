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

/** Serves as boilerplate code for creating Element subclasses
*/
class ColorWheelElement : public Element {
public:
	ColorWheelElement() {
		texture = NULL;
	}
	
	void draw(SDL_Renderer *renderer) {
		if (!texture) {
			int width = 256;
			int height = 256;
			texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
				SDL_TEXTUREACCESS_STREAMING, width, height);
			
			Pixel *pixels;
			int pitch;
			SDL_LockTexture(texture, NULL, (void **) &pixels, &pitch);
			
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					pixels[x + width * y].setRGBA(x, y, 0);
				}
			}
			
			SDL_UnlockTexture(texture);
		}
		
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	}
	
private:
	SDL_Texture *texture;
};


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
	display.add(new ColorWheelElement());
	display.start();
	
	// Cleanup
	SDL_Quit();
	
	return sin(3.14159265359);
}
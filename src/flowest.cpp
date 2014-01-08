#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <thread>
#include <SDL2/SDL.h>
#include "flowest.hpp"
#include "graphics.hpp"
#include "physics.hpp"


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
class ColorWheelElement : public TextureElement {
public:
	void paint(int width, int height, Pixel *pixels) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				pixels[x + width * y].setRGBA(x, y, 256 - (x + y) / 2);
			}
		}
	}
	
	bool isDirty() {
		return true;
		//Lulz -LAB
	}
};

/*
class SliceElement : public TextureElement {
public:
	Surface s; //Surface
	std::string f_d; //Fixed Dimension
	int loc; //Slice location in fixed dimension

	SliceElement(Surface *surface, std::string fixed_dim, int location) {
		s = surface;
		f_d = fixed_dim; *
		loc = location;
	}
	
	void paint(int width, int height, Pixel *pixels){
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				pixels[x + width * y].setRGBA(x, y, 0);
			}
		}

		//TODO: make sure the x_pos and y_pos are within 
		//the given width and height?
		for (Voxel *voxel : surface->voxels){
			x_pos = voxel.position.x
			y_pos = voxel.position.y
			pixels[x_pos + width * y_pos].setRGBA(10, 10, 10)
		}

	}
};
*/



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
	Display display("flowest", 256, 256, 2);
	
	WindTunnelElement *windTunnelElement = new WindTunnelElement();
	std::thread windTunnelThread(&WindTunnelElement::start, windTunnelElement);
	
	display.add(windTunnelElement);
	display.start();
	
	// windTunnelThread.join();
	delete windTunnelElement;
	
	// Cleanup
	SDL_Quit();
	
	return 0xaaaaaaaa & 0x55555555;
}
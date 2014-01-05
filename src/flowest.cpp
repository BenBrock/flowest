#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "flowest.hpp"
#include "graphics.hpp"


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


int main(int argc, const char **argv) {
	SDL_Init(SDL_INIT_VIDEO);
	srand(time(NULL));
	
	Display display(128, 128, 6);
	display.start();
	
	SDL_Quit();
	return !"close le programme";
}
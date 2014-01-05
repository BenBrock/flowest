#include "Surface.h"
#include "graphics.hpp"


void shadow(Surface *surface, SDL_Texture *texture) {
	Uint32 *pixels;
	int pitch;
	int width;
	int height;
	
	SDL_QueryTexture(texture, NULL,NULL,
										&width, &height);
	
	int err = SDL_LockTexture(texture, NULL, (void **) &pixels, &pitch);
	
	for (int i = 0; i < width * height; i++){
		pixels[i] = 0x000000FF;
	}
	
	for (int i = 0; i < surface->voxels.size(); i++){
		int scr_x = surface->voxels[i]->position.x; //Screen x
		int scr_y = surface->voxels[i]->position.z; //Screen y
		
		scr_x = scr_x + width/2;
		scr_y = scr_y + height/2;
		
		pixels[scr_x + width * scr_y] = 0xFFFFFFFF;
	}
	
	SDL_UnlockTexture(texture);
}


Display::Display(int width, int height, int zoom) {
	running = false;
	
	// Window
	const char *title = "flowest";
	int windowWidth = width * zoom;
	int windowHeight = height * zoom;
	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	  windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	
	// Renderer
	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	SDL_RenderSetScale(renderer, zoom, zoom);
	
	// Texture
	screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, width, height);
}

void Display::start() {
	running = true;
	while (running) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			checkEvent(event);
		}
		
		render();
	}
}

void Display::checkEvent(SDL_Event &event) {
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
	}
}

void Display::render() {
	// Clear the screen with black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	// Draw the texture
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
	
	SDL_RenderPresent(renderer);
}
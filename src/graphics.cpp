#include <stdlib.h>
#include "Surface.h"
#include "flowest.hpp"
#include "graphics.hpp"


// class Display

Display::Display(int width, int height, int zoom) {
	this->width = width;
	this->height = height;
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
	
	nextSurface = NULL;
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

SDL_Surface *Display::createNextSurface() {
	return SDL_CreateRGBSurface(0, width, height, 32,
		0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
}

void Display::setNextSurface(SDL_Surface *surface) {
	std::lock_guard<std::recursive_mutex> lock(surfaceMutex);
	if (nextSurface) {
		SDL_FreeSurface(nextSurface);
	}
	
	nextSurface = surface;
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
	
	// Create a new texture from the next surface
	{
		std::lock_guard<std::recursive_mutex> lock(surfaceMutex);
		if (nextSurface) {
			if (screenTexture) {
				SDL_DestroyTexture(screenTexture);
			}
			
			screenTexture = SDL_CreateTextureFromSurface(renderer, nextSurface);
			setNextSurface(NULL);
		}
	}
	
	// Draw the texture
	if (screenTexture) {
		SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
	}
	
	SDL_RenderPresent(renderer);
}

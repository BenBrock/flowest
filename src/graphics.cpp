#include <stdlib.h>
#include "Surface.h"
#include "flowest.hpp"
#include "graphics.hpp"


void Container::draw(SDL_Renderer *renderer) {
	// Draw the elements backwards
	for (Element *element : elements) {
		element->draw(renderer);
	}
}

void Container::add(Element *element) {
	elements.push_back(element);
}


// class Display

Display::Display(const char *title, int width, int height, int zoom) {
	running = false;
	
	// Window
	int windowWidth = width * zoom;
	int windowHeight = height * zoom;
	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	  windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	
	// Renderer
	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	SDL_RenderSetScale(renderer, zoom, zoom);
}

Display::~Display() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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
	
	draw(renderer);
	
	SDL_RenderPresent(renderer);
}


TextureElement::TextureElement() {
	texture = NULL;
}

TextureElement::~TextureElement() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void TextureElement::draw(SDL_Renderer *renderer) {
	// Lazily create the texture
	if (!texture) {
		// TODO
		// Generalize the width and height
		int width = 256;
		int height = 256;
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	}
	
	// Paint the texture
	if (isDirty()) {
		int width, height;
		int pitch;
		Pixel *pixels;
		
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);
		SDL_LockTexture(texture, NULL, (void **) &pixels, &pitch);
		check(width * sizeof(Pixel) == pitch, "Texture has unexpected pitch");
		
		paint(width, height, pixels);
		
		SDL_UnlockTexture(texture);
	}
	
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

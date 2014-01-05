#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>


struct Display {
	Display(int width, int height, int zoom=1);
	void start();
	
private:
	void checkEvent(SDL_Event &event);
	void render();
	
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *screenTexture;
	bool running;
};

#endif
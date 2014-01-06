#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <mutex>
#include <SDL2/SDL.h>


class Display {
public:
	Display(int width, int height, int zoom=1);
	void start();
	
	/** Generates a surface with proper size and pixel format
		to be drawn onto by a pixel source (such as a physics engine)
	*/
	SDL_Surface *createNextSurface();
	
	/** Gives back the surface created by createNextSurface() to be
		drawn to the screen in the next frame
	*/
	void setNextSurface(SDL_Surface *surface);
	
	bool running;
	
private:
	void checkEvent(SDL_Event &event);
	void render();
	
private:
	int width;
	int height;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *screenTexture;
	SDL_Surface *nextSurface;
	std::recursive_mutex surfaceMutex;
};

#endif
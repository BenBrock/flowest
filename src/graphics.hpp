#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <list>
#include <SDL2/SDL.h>


struct Pixel {
	// This order assumes little endian
	Uint8 a, b, g, r;
	
	inline void setRGBA(Uint8 r=0, Uint8 g=0, Uint8 b=0, Uint8 a=255) {
		this->r = r; this->g = g; this->b = b; this->a = a;
	}
};


class Element {
public:
	virtual void draw(SDL_Renderer *renderer) {}
};


class Container : public Element {
public:
	void draw(SDL_Renderer *renderer);
	void add(Element *element);
	// void remove(Element *element);
	
private:
	std::list<Element *> elements;
};


class Display : public Container {
public:
	Display(const char *title, int width, int height, int zoom=1);
	~Display();
	void start();
	
private:
	void checkEvent(SDL_Event &event);
	void render();
	
private:
	bool running;
	SDL_Window *window;
	SDL_Renderer *renderer;
};


class TextureElement : public Element {
public:
	TextureElement();
	~TextureElement();
	void draw(SDL_Renderer *renderer);
	
	virtual void paint(int width, int height, Pixel *pixels) {}
	virtual bool isDirty() { return true; }
	
private:
	SDL_Texture *texture;
};

#endif
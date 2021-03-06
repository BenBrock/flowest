#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <mutex>
#include "maths.hpp"
#include "graphics.hpp"

// TODO
// float computeAverageDrag(Surface *surface);


class WindTunnel {
public:
	WindTunnel();
	~WindTunnel();
	void start();
	void stop();
	void step();
	
	static const int w = 256;
	static const int h = 256;
	
	std::recursive_mutex stepMutex;
	
	FieldF *U;
private:
	float t;
	bool running;
};


class WindTunnelElement : public TextureElement {
public:
	WindTunnelElement();
	void start();
	void stop();
	
	void paint(int width, int height, Pixel *pixels);
	
private:
	WindTunnel *windTunnel;
};


#endif
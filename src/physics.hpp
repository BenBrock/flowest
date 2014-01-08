#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <mutex>
#include "graphics.hpp"

// TODO
// float computeAverageDrag(Surface *surface);


class WindTunnel;


class WindTunnelElement : public TextureElement {
public:
	WindTunnelElement();
	void start();
	
	void paint(int width, int height, Pixel *pixel);
	
private:
	WindTunnel *windTunnel;
};


#endif
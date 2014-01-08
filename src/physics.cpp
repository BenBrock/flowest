#include "physics.hpp"
#include <olb2D.h>
#include <olb2D.hh>

using namespace olb;

float omega = 1.0;
float r = 5.0;


#define DESCRIPTOR descriptors::D2Q9Descriptor


class WindTunnel {
public:
	WindTunnel();
	~WindTunnel();
	void start();
	void step();
	
	BlockLattice2D<float, DESCRIPTOR> *lattice;
	std::recursive_mutex mutex;
	
private:
	BGKdynamics<float, DESCRIPTOR> *bulkDynamics;
	OnLatticeBoundaryCondition2D<float, DESCRIPTOR> *boundaryCondition;
};



WindTunnel::WindTunnel() {
	// I think this is only required for OpenMPI initialization
	// Fake the command line arguments
	int argcFake = 0;
	olb::olbInit(&argcFake, NULL);
	
	// Create grid (lattice)
	int width = 256;
	int height = 256;
	
	lattice = new BlockLattice2D<float, DESCRIPTOR>(width, height);
	
	// Set up Lattice Boltzmann (Bhatnagar-Gross-Krook, BGK) dynamics model
	bulkDynamics = new BGKdynamics<float, DESCRIPTOR>(omega,
		instances::getBulkMomenta<float, DESCRIPTOR>());
	// The rectangular domain covers the entire lattice
	lattice->defineDynamics(0, width - 1, 0, height - 1, bulkDynamics);
	
	// Set boundary conditions
	boundaryCondition = createLocalBoundaryCondition2D(*lattice);
	boundaryCondition->addVelocityBoundary1P(
		width/2-16, width/2+16,
		height/2-16, height/2+16, omega);
	// boundaryCondition->addVelocityBoundary1N(width/2, width-32, height-32, height-32, omega);
	// boundaryCondition->addVelocityBoundary1N(1,width-2, 0, 0, omega);
	// boundaryCondition->addVelocityBoundary0N(0,0, 1, height-2, omega);
	// boundaryCondition->addPressureBoundary0P(width-1,width-1, 1, height-2, omega);
	lattice->initialize();
	
	// Set initial velocity and pressure (u and rho)
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float rho = 1.0;
			float u[2] = {0.0, 0.0};
			
			lattice->get(x, y).defineRhoU(rho, u);
		}
	}
}

WindTunnel::~WindTunnel() {
	delete lattice;
	delete bulkDynamics;
	delete boundaryCondition;
}

void WindTunnel::start() {
	for (;;) {
		step();
	}
}

void WindTunnel::step() {
	std::lock_guard<std::recursive_mutex> lock(mutex);
	
	// Define spatial conditions on each timestep
	float u[2] = {0.0, -0.1};
	for (int x = 64; x <= 256-64; x++) {
		lattice->get(x, 64).defineU(u);
	}
	
	lattice->collideAndStream();
}


WindTunnelElement::WindTunnelElement() {
	windTunnel = new WindTunnel();
}

void WindTunnelElement::start() {
	windTunnel->start();
}

void WindTunnelElement::paint(int width, int height, Pixel *pixel) {
	std::lock_guard<std::recursive_mutex> lock(windTunnel->mutex);
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float rho;
			float u[2];
			windTunnel->lattice->get(x, y).computeRhoU(rho, u);
			float uNorm = hypot(u[0], u[1]);
			pixel[x + width * y].setRGBA(1000 * uNorm, 1000 * fabs(rho - 1.0), 0);
		}
	}
}

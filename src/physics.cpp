#include "physics.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <olb2D.h>
#include <olb2D.hh>

using namespace olb;

#define DESCRIPTOR descriptors::D2Q9Descriptor
float omega = 1.0;
float r = 5.0;

int startWindTunnel() {
	// I think this is only required for OpenMPI initialization
	// Fake the command line arguments
	int argc = 0;
	olbInit(&argc, NULL);
	
	singleton::directories().setOutputDir("./output/");
	
	// Create grid (lattice)
	int width = 256;
	int height = 256;
	BlockLattice2D<float, DESCRIPTOR> lattice(width, height);
	
	// Set up Lattice Boltzmann (Bhatnagar-Gross-Krook, BGK) dynamics model
	BGKdynamics<float, DESCRIPTOR> bulkDynamics(omega,
		instances::getBulkMomenta<float, DESCRIPTOR>());
	// The rectangular domain covers the entire lattice
	lattice.defineDynamics(0, width - 1, 0, height - 1, &bulkDynamics);
	
	// Set boundary conditions
	OnLatticeBoundaryCondition2D<float, DESCRIPTOR> *boundaryCondition =
		createLocalBoundaryCondition2D(lattice);
	boundaryCondition->addVelocityBoundary1P(
		width/2-16, width/2+16,
		height/2-16, height/2+16, omega);
	// boundaryCondition->addVelocityBoundary1N(width/2, width-32, height-32, height-32, omega);
	// boundaryCondition->addVelocityBoundary1N(1,width-2, 0, 0, omega);
	// boundaryCondition->addVelocityBoundary0N(0,0, 1, height-2, omega);
	// boundaryCondition->addPressureBoundary0P(width-1,width-1, 1, height-2, omega);
	lattice.initialize();
	
	// Set initial velocity and pressure (u and rho)
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float rho = 1.0;
			float u[2] = {0.0, 0.0};
			
			lattice.get(x, y).defineRhoU(rho, u);
		}
	}
	
	// The timestep loop
	for (int i = 0; i < 1024; i++) {
		if (i % 4 == 0) {
			char filename[32];
			snprintf(filename, 32, "u%06d", i);
			
			graphics::ImageWriter<float> imageWriter("air");
			imageWriter.writeScaledGif(filename,
				lattice.getDataAnalysis().getVelocityNorm());
			printf("Wrote %s.gif\n", filename);
		}
		
		// Set velocity and pressure boundary conditions
		float u[2] = {0.0, -0.1};
		for (int x = 64; x <= width-64; x++) {
			lattice.get(x, 64).defineU(u);
		}
		
		lattice.collideAndStream();
	}
	
	delete boundaryCondition;
}
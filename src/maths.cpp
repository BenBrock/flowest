#include <stdio.h>
#include "maths.hpp"

// Not sure where to put this
#define DELTA_X 1.0
#define DELTA_Y 1.0


void FieldF::print() {
	printf("{\n");
	for (int y = 0; y < h; y++) {
		printf("\t");
		for (int x = 0; x < w; x++) {
			printf("%.2f ", at(x, y));
		}
		printf("\n");
	}
	printf("}\n");
}

float FieldF::laplacian(int x, int y) {
	return (atSafe(x - 1, y) - 2 * atSafe(x, y) + atSafe(x + 1, y)) / (DELTA_X * DELTA_X) +
		(atSafe(x, y - 1) - 2 * atSafe(x, y) + atSafe(x, y + 1)) / (DELTA_Y * DELTA_Y);
}

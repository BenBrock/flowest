#include <stdio.h>
#include "maths.hpp"


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
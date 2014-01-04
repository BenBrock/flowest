#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main(int argc, char **argv) {
	Vec3i v(1, 2, 3);
	Vec3i w = v;
	Vec3i u = w + v;
	
	printf("(%d, %d, %d)\n", u.x, u.y, u.z);
	
	return 0;
}
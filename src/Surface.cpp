#include "Surface.h"
#include <cstdio>
#include <cmath>

Surface::Surface(int n) : n(n)
{
  int i, j, k;
  int x, y, z;
  Voxel *v;

  d = round(pow(n, 1.0 / 3.0) / 2.0);

  this->n = (2 * d + 1) * (2 * d + 1) * (2 * d + 1);

  for (i = -d; i <= d; i++) {
    for (j = -d; j <= d; j++) {
      for (k = -d; k <= d; k++) {
        v = new Voxel(i, j, k);
        voxels.push_back(v);
      }
    }
  }
}

Voxel::Voxel(int x, int y, int z)
{
  int i;

  position.x = x;
  position.y = y;
  position.z = z;

  for (i = 0; i < D_LEN; i++) {
    adj[i] = NULL;
  }
}

void Surface::print()
{
  int i;

  printf("n: %d, d: %d\n", n, d);

  for (i = 0; i < voxels.size(); i++) {
    printf("i: %d, x: %d, y: %d, z: %d\n", i, voxels[i]->position.x, voxels[i]->position.y, voxels[i]->position.z);
  }
}

Surface::~Surface()
{
  int i;
  for (i = 0; i < voxels.size(); i++) {
    delete voxels[i];
  }
}

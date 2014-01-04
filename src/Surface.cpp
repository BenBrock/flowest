#include "Surface.h"
#include <cstdio>
#include <cstdlib>
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
}

void Surface::connect()
{
  int i, j;
  std::list <Voxel *>::iterator lit;

  for (i = 0; i < voxels.size(); i++) {
    while (voxels[i]->adj.size() > 0) {
      voxels[i]->adj.pop_front();
    }
  }

  for (i = 0; i < voxels.size(); i++) {
    for (j = i + 1; j < voxels.size(); j++) {
      if (abs(voxels[i]->position.x - voxels[j]->position.x) < 2 && abs(voxels[i]->position.y - voxels[j]->position.y) < 2 && abs(voxels[i]->position.z - voxels[j]->position.z) < 2) {
        voxels[i]->adj.push_back(voxels[j]);
        voxels[j]->adj.push_back(voxels[i]);
      }
    }
  }
}

void Surface::print()
{
  int i;
  std::list <Voxel *>::iterator lit;

  printf("n: %d, d: %d\n", n, d);

  for (i = 0; i < voxels.size(); i++) {
    printf("i: %d, x: %d, y: %d, z: %d\n", i, voxels[i]->position.x, voxels[i]->position.y, voxels[i]->position.z);
    printf("    c: %d\n", voxels[i]->adj.size());
    for (lit = voxels[i]->adj.begin(); lit != voxels[i]->adj.end(); lit++) {
      printf("    c: x: %d, y: %d, z: %d\n", (*lit)->position.x, (*lit)->position.y, (*lit)->position.z);
    }
  }
}

Surface::~Surface()
{
  int i;
  for (i = 0; i < voxels.size(); i++) {
    delete voxels[i];
  }
}

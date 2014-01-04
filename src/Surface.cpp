#include "Surface.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

Surface::Surface(int n) : n(n)
{
  int i, j, k;
  int x, y, z;
  Voxel *v;

  srand48(time(0));

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

bool Surface::permute(Voxel *v)
{
  int cur_try;
  std::vector <int> tries;

  while (tries.size() < 6) {
    cur_try = lrand48() % 6;
    if (find(tries.begin(), tries.end(), cur_try) == tries.end()) {
      tries.push_back(cur_try);
      switch (cur_try)
      {
        case UP:
          if (exists(v->position.x, v->position.y, v->position.z + 1)) continue;
          v->position.z = v->position.z + 1;
          if (check()) {
            return true;
          }
          break;
        case DOWN:
          if (exists(v->position.x, v->position.y, v->position.z - 1)) continue;
          v->position.z = v->position.z - 1;
          if (check()) {
            return true;
          }
          break;
        case X_POS:
          if (exists(v->position.x + 1, v->position.y, v->position.z)) continue;
          v->position.z = v->position.x + 1;
          if (check()) {
            return true;
          }
          break;
        case X_NEG:
          if (exists(v->position.x - 1, v->position.y, v->position.z)) continue;
          v->position.z = v->position.x - 1;
          if (check()) {
            return true;
          }
          break;
        case Y_POS:
          if (exists(v->position.x, v->position.y + 1, v->position.z)) continue;
          v->position.z = v->position.y + 1;
          if (check()) {
            return true;
          }
          break;
        case Y_NEG:
          if (exists(v->position.x, v->position.y - 1, v->position.z)) continue;
          v->position.z = v->position.y - 1;
          if (check()) {
            return true;
          }
          break;
      }
    }
  }
  return false;
}

bool Surface::check()
{
  int i;

  connect();

  for (i = 0; i < voxels.size(); i++) {
    if (voxels[i]->adj.size() == 0) return false;
  }
  return true;
}

void Surface::test_shit()
{
  int i;

  for (i = 0; i < 1000; i++) {
    permute(voxels[lrand48() % n]);
  }
}

bool Surface::exists(int x, int y, int z)
{
  int i;
  for (i = 0; i < voxels.size(); i++) {
    if (voxels[i]->position.x == x && voxels[i]->position.y == y && voxels[i]->position.z == z) {
      return true;
    }
  }
  return false;
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

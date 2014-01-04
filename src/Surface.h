#include <vector>
#include "vector.h"

typedef enum {
  UP,
  DOWN,
  X_POS,
  X_NEG,
  Y_POS,
  Y_NEG,
  D_LEN
  } Directions;

class Surface {
  public:
    int n; /* Number of blocks in surface. */
    int d;
    std::vector <class Voxel *> voxels;
    void print();
    Surface(int n);
    ~Surface();
};

class Voxel {
  public:
    Vec3i position;
    Voxel *adj[6];
    Voxel(int x, int y, int z);
};

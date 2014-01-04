#include <vector>
#include <list>
#include "vector.h"

class Surface {
  public:
    int n; /* Number of blocks in surface. */
    int d;
    std::vector <class Voxel *> voxels;
    void connect(); /* Set adj pointers. */
    void print();
    Surface(int n);
    ~Surface();
};

class Voxel {
  public:
    Vec3i position;
    std::list <Voxel *> adj;
    Voxel(int x, int y, int z);
};

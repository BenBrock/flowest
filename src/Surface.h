#include <vector>
#include <list>
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
    void connect(); /* Set adj pointers. */
    void permute();
    bool check(); /* Check if surface is valid. */
    bool exists(int x, int y, int z); /* Returns whether a voxel exists at x, y, z. */
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

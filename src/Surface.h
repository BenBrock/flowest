#include <vector>
#include <list>
#include "vector.hpp"

typedef enum {
  UP,
  DOWN,
  X_POS,
  X_NEG,
  Y_POS,
  Y_NEG,
  D_LEN
  } Directions;

class Population {
  public:
    int s; /* Size of population. */
    int v; /* Number of victors in each population. */
    double pv; /* Percentage of victors in each population. */
    std::list <class Surface *> surfaces;

    void evolve();

    Population();
};

class Surface {
  public:
    int n; /* Number of blocks in surface. */
    int d;
    double p; /* Probability of permutation. */
    double m; /* Maximum possible permutations. */
    double drag;
    std::vector <class Voxel *> voxels;

    void mutate(); /* Mutate surface in accordance with p and m. */
    void print();

    bool permute(Voxel *v); /* Attempt to permute Voxel to which v points. */
    bool check(); /* Check if surface is valid. */
    void connect(); /* Set adj pointers. */
    bool exists(int x, int y, int z); /* Returns whether a voxel exists at x, y, z. */

    Surface(int n);
    ~Surface();
};

class Voxel {
  public:
    Vec3i position;
    std::list <Voxel *> adj;

    Voxel(int x, int y, int z);
};

float computeAverageDrag(Surface *surface);

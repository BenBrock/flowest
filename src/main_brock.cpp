#include <iostream>
#include "Surface.h"
using namespace std;

int main(int argc, char **argv)
{
  int i;
  Surface *s;

  s = new Surface(64);

  s->connect();
  printf("First print...\n");
  s->print();

  printf("testing...\n");
  s->test_shit();

  printf("Second print...\n");
  s->print();

  printf("Deleting...\n");

  delete s;

  return 0;
}

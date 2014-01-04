#include <iostream>
#include "Surface.h"
#include "Render.h"
using namespace std;

int main(int argc, char **argv)
{
  int i;
  Surface *s;

  s = new Surface(64);

  s->connect();
  printf("First print...\n");
  s->print();

  printf("Second print...\n");
  s->print();

  display_window(s);

  printf("Deleting...\n");

  delete s;

  return 0;
}

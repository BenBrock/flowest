#include <iostream>
#include "Surface.h"
using namespace std;

int main(int argc, char **argv)
{
  int i;
  Surface *s;

  s = new Surface(64);

  s->connect();
  s->print();

  printf("%f\n", computeAverageDrag(s));

  delete s;

  return 0;
}

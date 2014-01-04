#include <iostream>
#include "Surface.h"
using namespace std;

int main(int argc, char **argv)
{
  Surface *s;
  s = new Surface(64);

  s->connect();
  s->print();

  delete s;

  return 0;
}

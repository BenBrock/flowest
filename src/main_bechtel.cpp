#include <iostream>
#include "Surface.h"
#include "Render.h"
using namespace std;

int main(int argc, char **argv)
{
  int i;
  Surface *s;

  s = new Surface(64);

  display_window(s);

  delete s;

  return 0;
}

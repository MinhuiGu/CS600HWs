#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "random_generator.h"

using namespace std;

int main(int argc, char* argv[])
{
  random_generator rg;
  char* r_st;

  for (int i = 0; i < atoi(argv[1]); i++)
    {
      r_st = rg.random_string(20);
      cout << r_st << endl;

      delete[] r_st;
    }

  return 0;
}


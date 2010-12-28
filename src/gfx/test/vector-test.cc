#include "../vector.h"
#include <stdio.h>
#include <string>

#include "test-macro.cc"

using namespace crml;

int main(){
  printf("Vector tests -------------------------------------------------------\n");
  Vector v0;
  Vector v1(1, 0);
  Vector v2(2, 0);
  Vector v3(3, 5);
  
  EQ(v1.Add(v1).Equal(v2), true);
  EQ(v1.Add(v0).Equal(v1), true);
  EQ(v1.Multiply(1).Equal(v1), true);

  EQ((v3.Normalize().Length() == 1.000), true);
  EQ((v3.Normalize().Length() == 1.001), false);
  LOG(v3.Normalize().ShowVector());
   
  return 0;
}

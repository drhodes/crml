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
  
  EQ(v3.Rotate(360).Equal(v3), true);
  printf("%s\n", v3.Rotate(360).ShowVector().c_str());
  printf("%s\n", v3.ShowVector().c_str());
  
  printf("v1.X(): %f\n", v1.X());
  printf("v1.Y(): %f\n", v1.Y());

  for (float64 i=0; i<=360; i+=90){
    Vector temp = v1.Rotate(i);
    printf("%f: %s\n", i, temp.ShowVector().c_str());
  }

  
  
  return 0;
}

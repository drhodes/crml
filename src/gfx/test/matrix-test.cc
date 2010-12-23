#include "../vector.h"
#include "../matrix.h"
#include "test-macro.cc"
#include <stdio.h>

using namespace crml;

int main(){
  printf("Matrix tests -------------------------------------------------------\n");    
  Matrix2 I; // identity.
  Matrix2 m0(0,0,0,0);
  Matrix2 m1(1,0,0,1);
  
  Matrix2 m2(1,2,3,4);
  Matrix2 m3(1,2,3,4);
  Matrix2 m4(1.234, 2.123, 345.345, 123.345);
  
  EQ(I.Equal(m1), true);
  EQ(m2.Equal(m3), true);
  EQ(m2.Equal(m1), false);
  EQ(m1.Equal(m1), true);
  EQ(m2.Equal(m2), true);
 
  //printf("%s\n", m1.ShowMatrix().c_str());  
  //printf("%s\n", m2.Multiply(m1).ShowMatrix().c_str());  
  //printf("%s\n", m1.Multiply(m2).ShowMatrix().c_str());
  
  EQ(m4.Multiply(I).Equal(m4), true);
  EQ(I.Multiply(m4).Equal(m4), true);
  EQ(m2.Multiply(m1).Equal(m2), true);
  EQ(m1.Multiply(m1).Equal(m1), true);
  EQ(m1.Multiply(m0).Equal(m0), true);
  EQ(m0.Multiply(m1).Equal(m0), true); 


  Matrix2 rotmat;
  Vector v1(1,1);
  Vector v2(2,2);
  
  EQ(rotmat.Scale(2, v1).Equal(v2), true);
  
  printf("\nDone.\n");
  return 0;
}

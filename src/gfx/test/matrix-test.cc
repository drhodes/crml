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

  EQ(I.Equal(m1), true);
  EQ(m1.Multiply(m1).Equal(m1), true);
  EQ(m1.Multiply(m0).Equal(m0), true);
  EQ(m0.Multiply(m1).Equal(m0), true); 
  
  Matrix2 m2(1,2,3,4);
  Matrix2 m3(1,2,3,4);
  Matrix2 m4(1.234, 2.123, 345.345, 123.345);
 
  EQ(m2.Equal(m3), true);
  EQ(m2.Equal(m1), false);
  EQ(m1.Equal(m1), true);    
  EQ(m4.Multiply(I).Equal(m4), true);
  EQ(I.Multiply(m4).Equal(m4), true);
  EQ(m2.Multiply(m1).Equal(m2), true);

  Matrix2 mat;
  Vector v1(1,1);  
  Vector v2(2,2);
  Vector v3(1,0);
  Vector v4(0,1);
  Vector v5(-1,0);
  
  EQ(mat.Scale(2, v1).Equal(v2), true);
  EQ(mat.Rotate(90, v3).Equal(v4), true);
  EQ(mat.Rotate(180, v3).Equal(v5), true);

  Vector v6 = mat.Rotate(90, v3);
  EQ(mat.Rotate(90, v6).Equal(v5), true);
  
  Vector v7(2,3);
  Vector v8(4,3);
  Vector v9(2,6);
  
  EQ(mat.ScaleX(2, v7).Equal(v8), true);
  EQ(mat.ScaleY(2, v7).Equal(v9), true);
  
  Vector v10(1,1);
  Vector v11(2,1);
  Vector v12(1,2);
  
  EQ(mat.ShearX(0, v10).Equal(v10), true);
  EQ(mat.ShearX(1, v10).Equal(v11), true);
  EQ(mat.ShearY(0, v10).Equal(v10), true);
  EQ(mat.ShearY(1, v10).Equal(v12), true);

  // This assumption is wrong, but I'm leaving it here
  // so I don't forget about it.  
  // Vector v13 = mat.ScaleX(2, v8);
  // Vector v14 = mat.ShearX(2, v8);  
  // LOG(v13.ShowVector());
  // LOG(v14.ShowVector());  
  // EQ(mat.ShearX(2, v8).Equal(v13), true);  <-- not true.


  // next check GlMatrix()  
  EQ(mat.GlMatrix() == mat.GlMatrix(), true);
  //  EQ(mat.GlMatrix()[0] == mat., true);
  

  
  
  printf("\nDone.\n");
  return 0;
}

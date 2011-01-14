#include "../rect.h"
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

  Vector v0(0,0);
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
  
  Rect r1(-50, -50, 50, 50);
  mat.Scale(2).Rotate(45).Transform(r1);
  LOG(r1.ShowRect());
  
  EQ(r1.TopLeft().Equal(Vector(0, -141.421356)), true);  
  EQ(r1.TopRight().Equal(Vector(141.421356, -0.000000)), true);
  EQ(r1.BottomLeft().Equal(Vector(-141.421356, 0.000000)), true);
  EQ(r1.BottomRight().Equal(Vector(0.000000, 141.421356)), true);
 
  Rect r2(-10, -10, 10, 10);
  mat.ShearX(3, r2);
  LOG(r2.ShowRect());

  EQ(r2.TopLeft().Equal(Vector(-40.000000, -10.000000)), true);
  EQ(r2.TopRight().Equal(Vector(-20.000000, -10.000000)), true);
  EQ(r2.BottomLeft().Equal(Vector(20.000000, 10.000000)), true);
  EQ(r2.BottomRight().Equal(Vector(40.000000, 10.000000)), true);

  EQ(I.TranslateVector(v0).Equal(v0), true);
  EQ(I.TranslateVector(v1).Equal(v1), true);
  
  Matrix2 trans;
  trans.TranslateUpdate(v1);
  EQ(trans.Transform(v0).Equal(v1), true);
  LOG(trans.Transform(v0).ShowVector());
  
  LOG(trans.ShowMatrix());
  
  LOG(I.Translate(v1).TranslateVector(v0).ShowVector());
  EQ(I.Translate(v1).Transform(v0).Equal(v1), true);

  Rect r3(0, 0, 10, 10);
  trans.Translate(v1, r3);
  EQ(r3.TopLeft().Equal(Vector(1, 1)), true);
  EQ(r3.TopRight().Equal(Vector(11, 1)), true);
  EQ(r3.BottomLeft().Equal(Vector(1, 11)), true);
  EQ(r3.BottomRight().Equal(Vector(11, 11)), true);

  Rect r4(0, 0, 10, 10);
  trans.Translate(v1, r4);
  EQ(r4.TopLeft().Equal(Vector(1, 1)), true);
  EQ(r4.TopRight().Equal(Vector(11, 1)), true);
  EQ(r4.BottomLeft().Equal(Vector(1, 11)), true);
  EQ(r4.BottomRight().Equal(Vector(11, 11)), true);
    
  
  Vector v23(2,3);  
  TRUE( mat.Scale(.5, v23).Equal(Vector(1,1.5)) );

  Matrix2 trans2;
  trans2.ScaleUpdate(.5);
  trans2.TranslateUpdate(v23);
  EQ(trans2.Transform(v0).Equal(v23), true);
  LOG(trans2.Transform(v0).ShowVector());



  printf("\nDone.\n");
  return 0;
}

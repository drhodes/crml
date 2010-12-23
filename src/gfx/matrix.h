// -*- c++ -*-
// _.-{{crml}}-._

#ifndef MATRIX_H_
#define MATRIX_H_

#include "../core/crmltypes.h"
#include "./vector.h"

namespace crml {

class Matrix2 {
 public:
  explicit Matrix2(){
    r1c1_ = 1; r1c2_ = 0;
    r2c1_ = 0; r2c2_ = 1;      
  }

  explicit Matrix2( float64 r1c1, float64 r1c2, float64 r2c1, float64 r2c2){
    r1c1_ = r1c1; r1c2_ = r1c2;
    r2c1_ = r2c1; r2c2_ = r2c2;
  }

  bool Equal(Matrix2& other);  
  Matrix2 Multiply(Matrix2& other);
  Vector Transform(Vector& v);
  
  Matrix2 Scale(float64 s);
  void ScaleUpdate(float64 s);
  Vector Scale(float64 s, Vector& v);
  
  Matrix2 Rotate(float64 theta);
  void RotateUpdate(float64 theta);
  Vector Rotate(float64 theta, Vector& v);
  
  Vector Shear(float64 n);
  void ShearUpdate(float64 n);
  Vector Shear(float64 n, Vector& v);

  Vector Reflect(float64 n);
  void ReflectUpdate(float64 n);
  Vector Reflect(float64 n, Vector& v);

  void CopyInto(Matrix2& other);
  std::string ShowMatrix();
  
 private:
  float64 r1c1_, r1c2_, r2c1_, r2c2_;
};

}       // namespace crml
#endif  // MATRIX2_H_












// -*- c++ -*-
// _.-{{crml}}-._

#ifndef MATRIX_H_
#define MATRIX_H_

#include "../core/crmltypes.h"
#include "./vector.h"
#include "./rect.h"
#include <vector>

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
  Vector Transform(Vector v);
  void Transform(Rect& v);

  std::vector<float64> GlMatrix();
  
  Matrix2 Scale(float64 s);
  Vector Scale(float64 s, Vector& v);
  void Scale(float64 s, Rect& v);
  void ScaleUpdate(float64 s);

  Matrix2 ScaleX(float64 s);
  Vector ScaleX(float64 s, Vector& v);
  void ScaleX(float64 s, Rect& v);
  void ScaleXUpdate(float64 s);

  Matrix2 ScaleY(float64 s);
  Vector ScaleY(float64 s, Vector& v);
  void ScaleY(float64 s, Rect& v);
  void ScaleYUpdate(float64 s);
  
  Matrix2 Rotate(float64 theta);
  Vector Rotate(float64 theta, Vector& v);
  void Rotate(float64 theta, Rect& v);
  void RotateUpdate(float64 theta);
  
  Matrix2 ShearX(float64 n);
  Vector ShearX(float64 n, Vector& v);
  void ShearX(float64 n, Rect& v);
  void ShearXUpdate(float64 n);
  
  Matrix2 ShearY(float64 n);
  Vector ShearY(float64 n, Vector& v);
  void ShearY(float64 n, Rect& v);
  void ShearYUpdate(float64 n);
  
  Matrix2 Reflect(float64 n);
  Vector Reflect(float64 n, Vector& v);
  void Reflect(float64 n, Rect& v);
  void ReflectUpdate(float64 n);
  
  void CopyInto(Matrix2& other);
  std::string ShowMatrix();
  
 private:
  float64 r1c1_, r1c2_, r2c1_, r2c2_;
};

}       // namespace crml
#endif  // MATRIX2_H_

// -*- c++ -*-
// _.-{{crml}}-._

#ifndef MATRIX_CC
#define MATRIX_CC

#include "./matrix.h"

namespace crml {

bool Matrix2::Equal(Matrix2& other){
  return ( r1c1_ == other.r1c1_ &&
           r1c2_ == other.r1c2_ &&
           r2c1_ == other.r2c1_ &&
           r2c2_ == other.r2c2_ );
}

Matrix2 Matrix2::Multiply(Matrix2& other){
  Matrix2 result;
  // a11*b11 + a12*b21                      
  result.r1c1_ = r1c1_ * other.r1c1_ +
                 r1c2_ * other.r2c1_;
  // a11*b12 + a12*b22
  result.r1c2_ = r1c1_ * other.r1c2_ +
                 r1c2_ * other.r2c2_;
  // a21*b11 + a22*b21
  result.r2c1_ = r2c1_ * other.r1c1_ +
                 r2c2_ * other.r2c1_;
  // a21*b12 + a22*b22
  result.r2c2_ = r2c1_ * other.r1c2_ +
                 r2c2_ * other.r2c2_;    
  return result;  
}

void Matrix2::CopyInto(Matrix2& other){
  other.r1c1_ = r1c1_;
  other.r1c2_ = r1c2_;
  other.r2c1_ = r2c1_;
  other.r2c2_ = r2c2_;
}

Matrix2 Matrix2::Scale(float64 s){
  Matrix2 result;
  result.ScaleUpdate(s);
  return result;
}

Vector Matrix2::Scale(float64 s, Vector& v){
  Matrix2 result;
  result.ScaleUpdate(s);
  return result.Transform(v);
}

void Matrix2::ScaleUpdate(float64 s){
  r1c1_ *= s;
  r2c2_ *= s;
}

Matrix2 Matrix2::Rotate(float64 theta){  
  Matrix2 result;
  float64 degs = theta / 57.295779513082323;

  result.r1c1_ = +cos(degs);
  result.r1c2_ = -sin(degs);
  result.r2c1_ = +sin(degs);
  result.r2c2_ = +cos(degs);

  return result;
  //x__ = +x_ * cos(degs) -y_ * sin(degs);
  //y__ = +x_ * sin(degs) +y_ * cos(degs); 
}

Vector Matrix2::Rotate(float64 angle, Vector& v){
  Matrix2 result;
  return result.Rotate(angle).Transform(v);
}

/*
Vector Vector::Shear(Vector& v){ 
}

Vector Vector::Reflect(Vector& v){
  
}
*/

Vector Matrix2::Transform(Vector& v){
  float64 x = r1c1_ * v.X() + r1c2_ * v.Y();
  float64 y = r2c1_ * v.X() + r2c2_ * v.Y();
  return Vector(x,y);
}

std::string Matrix2::ShowMatrix() {
  char buffer[100];  
  sprintf(buffer, "\n|%3.2f, %3.2f|\n|%3.2f, %3.2f|\n",
          r1c1_, r1c2_, r2c1_, r2c2_);  
  return std::string(buffer);
}



}       // namespace crml
#endif  // MATRIX2_CC












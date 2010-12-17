// Copyright 2010 <Derek A. Rhodes>

#ifndef VECTOR_CC
#define VECTOR_CC

#include "./vector.h"

namespace crml {

Vector::Vector() {
  x_ = 0;
  y_ = 0;     
}

Vector::Vector(float64 x, float64 y) {
  x_ = x;
  y_ = y;     
}


Vector::Vector(const Vector& v){
  x_ = v.x_;
  y_ = v.y_;      
}

Vector::~Vector() {
}

void Vector::XY(float64 x, float64 y) {
  x_ = x;
  y_ = y;
}

float64 Vector::X() {
  return x_;
}

void Vector::X(float64 x) {
  x_= x;
}

float64 Vector::Y() {
  return y_;
}

void Vector::Y(float64 y) {
  y_ = y;
}

float64 Vector::Distance(Vector* other){
  // consider the quake optimization.
  return sqrt((x_ - other->x_)*(x_ - other->x_) +
              (y_ - other->y_)*(y_ - other->y_));  
}

float64 Vector::Length() {
  return sqrt(x_*x_ + y_*y_);
}


// given a grid with spacing <res>
// floor x and y to the closest grid intersection.
Vector Vector::Align(int32 res){
  float64 snap_x = X() - float64(int32(X()) % res );
  float64 snap_y = Y() - float64(int32(Y()) % res );

  return Vector(snap_x, snap_y);
}


}       // namespace crml
#endif  // VECTOR_CC

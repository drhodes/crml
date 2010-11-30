// Copyright 2010 <Derek A. Rhodes>

#ifndef VECTOR_CC
#define VECTOR_CC

#include "./vector.h"

namespace crml {

Vector::Vector() {
  x_ = 0;
  y_ = 0;     
}

Vector::Vector(int x, int y) {
  x_ = x;
  y_ = y;     
}

Vector::~Vector() {
}

void Vector::XY(int x, int y) {
  x_ = x;
  y_ = y;
}

int Vector::X() {
  return x_;
}

void Vector::X(int x) {
  x_= x;
}

int Vector::Y() {
  return y_;
}

void Vector::Y(int y) {
  y_ = y;
}

int Vector::Distance(Vector* other){
  // consider the quake optimization.
  return sqrt((this->x_ - other->x_)*(this->x_ - other->x_) +
              (this->y_ - other->y_)*(this->y_ - other->y_));
  
}

int Vector::Length() {
  return sqrt(x_*x_ + y_*y_);
}

Vector Vector::Align(int res){
  Vector v(X()-(X()%res), Y()-(Y()%res));
  return v;
}


}       // namespace crml
#endif  // VECTOR_CC
